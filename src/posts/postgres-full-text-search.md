---
title: "Postgres Full Text Search"
date: "2021-04-22"
description: ""
layout: layouts/post.njk
permalink: "/posts/{{ title | slug }}/"
cssclass: "post-container"
tags:
  - posts
  - docker
  - postgres
  - sql
---

Today, I want to talk about how easy it is to implement a full-text search in 
Postgres. Let's dive right into it!

But first, why you would want to implement text search when you can do queries 
with `LIKE` or `ILIKE`. There are many reasons to this:

- Full-text search queries against a specialized [stemmed](https://en.wikipedia.org/wiki/Stemming) 
  version of your data. This means that it can search for complex English words 
  like "justifiable" when searching for "justify".

- It is fast, especially combined with indexes. LIKE and ILIKE will have to do a
  sequential scan of your data to select the results.

- You can blacklist certain words from getting parsed.

And much more!

## Setup


#### Postgres Instance

I am using [docker](https://www.docker.com/) to create a new postgres instance 
on my local machine. To create start a Postgres container, run:

```shell
docker run --name=postgresfts -p 5432:5432 -e POSTGRES_PASSWORD=postgres -d postgres
```

Feel free to use any frontend clients you like to connect to this postgres instance.
For this job, `psql` will do fine.

#### Sample Data

We need some data to search. For this I am using the example of a books table 
that looks like this:

```shell
                              Table "public.books"
   Column    |  Type   | Collation | Nullable |              Default
-------------+---------+-----------+----------+-----------------------------------
 id          | bigint  |           | not null | nextval('books_id_seq'::regclass)
 title       | text    |           |          |
 description | text    |           |          |
 price       | numeric |           |          |
Indexes:
    "books_pkey" PRIMARY KEY, btree (id)
```

To create this books table, run:

```sql
CREATE TABLE books (id BIGSERIAL PRIMARY KEY, title text, description text, price numeric);
```

Now that we have our table, let's fill in some data to work with. Inserting few 
rows are fine. But we are doing a full-text search and it is good to have few 
thousand rows to spice things up 😉.

For this, I have put together this simple nodejs script:

```js
const { Pool } = require("pg");
const format = require("pg-format");
const faker = require("faker");

const db = new Pool({
  host: "172.17.0.1", // postgres host
  database: "postgres",
  password: "passwd",
  user: "postgres",
});

async function main() {
  let books = [];

  for (let i = 1; i <= 100000; i++) {
    books[i - 1] = [
      faker.commerce.productName(),
      faker.commerce.productDescription(),
      faker.commerce.price(),
    ];
  }

  const query = format(
    "INSERT INTO books (title, description, price) VALUES %L",
    books
  );

  try {
    await db.query(query);
    console.log("Done!");
  } catch (error) {
    console.error(error);
  }
}

main();
```
The above script will create 100k rows using faker.js and insert them in the books table.

You can also clone this git repo from [siddhantk232/node_postgres_scripts](https://github.com/siddhantk232/node_postgres_scripts).

## Let's Search!

Now that we have our data ready in the books table. Let's implement full-text 
search.

In Postgres, you need two things to start with, one is a `tsvector` to search and
the other is the search query aka the `tsquery`.

#### tsvector?

The tsvector can be another column in your table that stores normalized keywords 
from the actual data.

In this case, I want the book's title and description column to be searchable. 
So I would create a tsvector of these columns.

Doing that is pretty easy, we can create a generated column of type tsvector.

To do this, run:

```sql
ALTER TABLE books ADD COLUMN fts tsvector 
  GENERATED ALWAYS AS (to_tsvector('english', title || ' ' || description)) 
  STORED;
```

This will add a column called `fts` to the books table. While inserting you have
to ignore this column as this is a generated column.

> The first argument to the `to_tsvector` is the language we are using. The default
> gets picked up from the instance's locale settings. You can change this to work with 
> other languages.

Now that we have our data and the tsvector, let's do some search!

For searching, we use the `@@` operator in Postgres. `@@` returns true if the 
search succeeds and false otherwise.

Example:

```sql
SELECT title FROM books WHERE fts @@ plainto_tsquery('chip') LIMIT 2;
```
I was getting a few thousand results which were hard to show, so I put a limit
of two here.

The output looks like this:

```shell
           title
---------------------------
 Refined Metal Chips
 Intelligent Granite Chips
(2 rows)
```

As you can see our search works. We searched for the chip and it returned the 
first two results it found.

## But how fast?

Let's analyze the search, but this time with a new query so that we don't hit 
the cache and get raw results.

```sql
EXPLAIN ANALYZE 
  SELECT id, title, description, price 
  FROM books WHERE fts @@ plainto_tsquery('style');
```

This will output:

```shell
                                                        QUERY PLAN
---------------------------------------------------------------------------------------------------------------------------
 Gather  (cost=1000.00..17860.20 rows=8297 width=150) (actual time=0.578..95.603 rows=8329 loops=1)
   Workers Planned: 2
   Workers Launched: 2
   ->  Parallel Seq Scan on books  (cost=0.00..16030.50 rows=3457 width=150) (actual time=0.461..86.162 rows=2776 loops=3)
         Filter: (fts @@ plainto_tsquery('style'::text))
         Rows Removed by Filter: 30557
 Planning Time: 0.191 ms
 Execution Time: 96.159 ms
(8 rows)
```

You can see we are getting about 8000 results in about 100ms! This is fast but 
we can do better.

## Index to the rescue!

Postgres recommends using a `GIN` index. Actually, You can use either `GIN` or
the `GiST` index type. You can learn the differences between them [here](https://www.postgresql.org/docs/13/textsearch-indexes.html).

Let's create a GIN index on our `fts` column:

```sql
CREATE INDEX books_search_idx ON books USING GIN (fts);
```

You can run `\d books` to see the created index in the psql client. The output 
will look something like this:

```shell
                                                                Table "public.books"
   Column    |   Type   | Collation | Nullable |                                               Default
-------------+----------+-----------+----------+-----------------------------------------------------------------------------------------------------
 id          | bigint   |           | not null | nextval('books_id_seq'::regclass)
 title       | text     |           |          |
 description | text     |           |          |
 price       | numeric  |           |          |
 fts         | tsvector |           |          | generated always as (to_tsvector('english'::regconfig, (title || ' '::text) || description)) stored
Indexes:
    "books_pkey" PRIMARY KEY, btree (id)
    "books_search_idx" gin (fts)
```

Let's try our search once again to see how much faster it is:

```shell
                                                           QUERY PLAN
--------------------------------------------------------------------------------------------------------------------------------
 Bitmap Heap Scan on books  (cost=84.55..7554.73 rows=8297 width=150) (actual time=4.786..17.013 rows=8329 loops=1)
   Recheck Cond: (fts @@ plainto_tsquery('style'::text))
   Heap Blocks: exact=4127
   ->  Bitmap Index Scan on books_search_idx  (cost=0.00..82.47 rows=8297 width=0) (actual time=3.125..3.126 rows=8329 loops=1)
         Index Cond: (fts @@ plainto_tsquery('style'::text))
 Planning Time: 0.425 ms
 Execution Time: 18.217 ms
(7 rows)
```

8k results in ~20ms in a 100k row table. This is crazy fast!

## The End

There is a lot that you can do with text search in Postgres. It is impossible to 
cover all of them in a single blog.

### Further readings

- [Postgres docs on full text search](https://www.postgresql.org/docs/13/textsearch.html)
- [Postgres text search index types](https://www.postgresql.org/docs/13/textsearch-indexes.html)
