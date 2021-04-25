---
title: "Notification service in webapps using custom javascript Events"
date: "2020-07-01"
description: "Build custom notfications service using custom events in javascript"
layout: layouts/post.njk
permalink: "/posts/{{ title | slug }}/"
cssclass: "post-container"
tags:
  - posts
---

Recently I came across this [article](https://flaviocopes.com/javascript-custom-events/) by **Flavio copes** on "Custom events in javascript" and after reading that I got the idea for this post.

So today we will implement a simple notification service built using vanilla js :)

I am going to integrate this notification service in a todo app that I have created. You can find the finished code [here](https://github.com/siddhantk232/custom-js-event-example)

## let's take a look at the code.

`index.html`

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <link rel="stylesheet" href="style.css" />
    <title>Document</title>
  </head>
  <body>
    <main>
      <form>
        <div>
          <input placeholder="todo" type="text" name="todos" id="todo" />
        </div>
        <button type="submit">add todo</button>
      </form>

      <ul id="todos"></ul>

      <div id="notify"></div>
    </main>

    <script src="main.js"></script>
  </body>
</html>
```

Here I have a simple form with an `input:text` and `button:submit`. And I also have a `ul#todos` for injecting in the todos. Other than that we also have a `div#notify`, we will use this to position our notification container on the top-right of the screen.

`style.css`

```css
body {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
  font-family: Arial, Helvetica, sans-serif;
  background-color: rgb(20, 20, 20);
  width: 100%;
  height: 100vh;
}

form {
  display: flex;
  align-items: center;
  justify-content: center;
  width: 100%;
  margin-top: 30px;
}

button {
  color: #ffffff;
  background-color: rgb(73, 129, 233);
  border: 0;
  cursor: pointer;
  margin-left: 10px;
}

input,
button {
  padding: 10px 20px;
}

ul {
  display: none;
  list-style: none;
  width: 50%;
  margin: 30px auto;
  border-radius: 4px;
  background-color: rgb(157, 185, 236);
  padding: 20px;
}

li {
  margin: 15px 0;
  border-bottom: 1px solid rgb(65, 83, 116);
}

.add-display {
  display: block;
}

.notification-container {
  padding: 10px 15px;
  background-color: rgb(130, 151, 190);
}

#notify {
  width: 20%;
  position: fixed;
  top: 20px;
  right: 30px;
  border-radius: 4px;
}
```

Pretty basic, right?

Apart from the basic form and body styles, I have added `position: fixed;` on the `#notify` div. This will prevent the notification container from moving onScroll.
Also, I have the `.notification-container` which we are using in the javascript.

`main.js`

```javascript
const form = document.forms[0];
const notificationHolder = document.querySelector("#notify");

const notify = new Event("notify");

form.addEventListener("submit", e => {
  e.preventDefault();
  const todo = form.getElementsByTagName("input")[0];

  window.todos.innerHTML += `
  
  	<li>${todo.value}</li>
  
  `;

  todo.value = "";

  document.dispatchEvent(notify);

  setTimeout(() => {
    notificationHolder.innerHTML = "";
  }, 2500);

  window.todos.classList.add("add-display");
});

document.addEventListener("notify", (...e) => {
  const container = document.createElement("div");

  container.classList.add("notification-container");
  container.innerHTML = `Todo added !`;

  notificationHolder.insertAdjacentElement("beforeend", container);
});
```

Here, we are using listening on the `submit` form event to add todos in our `ul#todos`.

Just below that, we have one more event listener which is listening for the `notify` event, that's is a custom event that we have created. Let's focus on the lines which are used to create this custom event.

so on top we have:

```javascript
const notify = new Event("notify");
```

We are using the [Event](https://developer.mozilla.org/en-US/docs/Web/API/Event) constructor to register a new event with the name 'notify' in our code. The name here is important because we will use this name only to listen for this custom event in our code.

Now in the `submit` listener callback function we are using `document.dispatchEvent(notify);` to trigger this event. Also, we are setting a timeout function to clear all notification after 2.5 seconds (minimum).

In the end, we are listening to our custom event `notify` and inserting a new notification container inside our `div#notify`.

That's it. Our notification service is ready. I know you might have some questions, let's address them below:

### Questions

#### what about modularity?

well, this was just a todo app and the implementation of custom events here is so small. If you have a big app that is using plain HTML, CSS, and js, then you can have a separate file that has custom Event declared and export functions for dispatching that event, and you can listen for that specific event in that file only.

If your project uses libraries like react or vue and state machines like mobX or redux then you may not need to write custom Event yourself.

#### How to pass custom notification message?

Well, I do not have an answer for how to pass something when dispatching the event and use that passed value in the callback function of a custom event listener. So you know then please share.

If I had to fire multiple notifications like `todo added`, `logged in`, and `logged out` I would create a new `Event` for each of them.

If you are on twitter, consider following [me](https://twitter.com/siddhantk232).
