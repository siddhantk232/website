---
title: "Postgres Triggers"
date: "2021-04-09"
description: "Let's use postgres triggers to solve a pretty common problem of an ecommerce web service."
layout: layouts/post.njk
permalink: "/posts/{{ title | slug }}/"
cssclass: "post-container"
canonical: "/posts/postgres-triggers"
tags:
  - posts
  - postgres
  - sql
---

Today in this blog, I want to talk about Postgres triggers. I will also go 
through an example use case to learn how to use it.

## The Scenario

I have an e-commerce app to sell books and I am implementing the cart functionality in 
the database. So, there is a carts table that stores unique cart entries per user 
and a books table. For cart items, we have another table, `carts_books`. The `carts` 
and `carts_books` are using a many-to-many relation. So, A cart can have many books, 
and a book can be used in many carts.

Whenever a row is inserted or updated in the `carts_books` table, I want to 
calculate the total price of the cart used. I also want to take the `multiplier` 
column of the `carts_books` table into account. This `multiplier` column is the 
quantity of a single book. That means I am allowing a customer to buy many copies 
of a book.


Let's use Postgres triggers to solve this problem. Before that, below is the list 
of columns of every table discussed so far.

### The schema

```shell
                               Table "public.carts"
   Column    |           Type           | Collation | Nullable |      Default
-------------+--------------------------+-----------+----------+--------------------
 created_at  | timestamp with time zone |           | not null | now()
 updated_at  | timestamp with time zone |           | not null | now()
 archived_at | timestamp with time zone |           |          |
 amount      | numeric                  |           | not null |
 status      | text                     |           | not null | 'ENQUEUED'::text
 user_id     | text                     |           | not null |
 id          | uuid                     |           | not null | gen_random_uuid()


                                     Table "public.books"
   Column    |           Type           | Collation | Nullable |              Default
-------------+--------------------------+-----------+----------+-----------------------------------
 created_at  | timestamp with time zone |           | not null | now()
 updated_at  | timestamp with time zone |           | not null | now()
 archived_at | timestamp with time zone |           |          |
 name        | text                     |           | not null |
 price       | numeric                  |           | not null |
 user_id     | bigint                   |           | not null |
 id          | bigint                   |           | not null | nextval('books_id_seq'::regclass)
 description | text                     |           | not null |

              Table "public.carts_books"
   Column   |  Type   | Collation | Nullable | Default
------------+---------+-----------+----------+---------
 book_id    | bigint  |           | not null |
 multiplier | integer |           | not null |
 user_id    | text    |           | not null |
 cart_id    | uuid    |           | not null |
```

## The Solution

We want to run a procedure (also known as a function) after a row in the table
`carts_books` is INSERTED or UPDATED.

For this let's create two postgres triggers, one for UPDATE and the other for INSERT.

```sql
CREATE TRIGGER update_cart_price
  AFTER UPDATE ON public.carts_books
  FOR EACH ROW
  EXECUTE PROCEDURE public.update_cart_price ();

COMMENT ON TRIGGER update_cart_price ON public.carts_books IS 
'update the price of the related cart based on the updated cart item(s) in relation carts_books';

CREATE TRIGGER calculate_cart_price
  AFTER INSERT ON public.carts_books
  FOR EACH ROW
  EXECUTE PROCEDURE public.update_cart_price ();

COMMENT ON TRIGGER calculate_cart_price ON public.carts_books IS 
'update the price of the related cart based on the updated cart item(s) in relation carts_books';
```
Above is the code that creates two postgres triggers. Let's understand the syntax 
and what each clause used above means.

To create a postgres trigger, we want to tell postgres about the following things:

1. Name of the trigger. In this case, I have used names, `update_cart_price` and 
  `calculate_cart_price`.

2. When you want the code to run? I want to know the values that are inserted, 
  for this, I have to use the `AFTER INSERT` and the `AFTER UPDATE` clause.

3. How do you want to run this trigger? There are two options, one is to run this 
  trigger for each affected row. Another option is to run the trigger `per-statement`.

4. What do you want to run? I have these triggers to run the procedure called 
  `update_cart_price()`. 

> You must create the function before using it in a trigger.
> A function must return `TRIGGER` in order to be used in a trigger.

The function that I want to run on these triggers is defined as:

```plsql
CREATE OR REPLACE FUNCTION public.update_cart_price ()
  RETURNS TRIGGER
  AS $$
DECLARE
  item record;
  new_amount numeric := 0;
BEGIN
  FOR item IN
  SELECT
    price,
    multiplier
  FROM
    carts_books
    JOIN books ON book_id = books.id
  WHERE
    cart_id = NEW.cart_id LOOP
      new_amount := new_amount + (item.price * item.multiplier);
    END LOOP;
  UPDATE
    carts
  SET
    amount = new_amount
  WHERE
    id = NEW.cart_id;
  RETURN new;
END;
$$
LANGUAGE plpgsql;
```

This function selects the price and multiplier of all the books used inside the 
cart. It then updates the cart's amount column to reflect the updated amount.

The data of the changed row is made available through the `new` record.

Also, the function cannot use plain `SQL` language, you must use a procedural
language.

## The Conclusion

Postgres triggers make it easy to execute small business logic on data changes. 
Also, we do not need to care about the network latency that we would face if we 
execute the same logic in a different service (a nodejs app for example).

### Good Reads

In addition to this post, I also recommend reading these to know more about postgres
triggers.

* [Official Docs](https://www.postgresql.org/docs/13/trigger-definition.html)

* [Data visibility in trigger functions](https://www.postgresql.org/docs/13/trigger-datachanges.html)
