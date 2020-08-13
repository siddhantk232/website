---
title: "testing web apps with cypress | Siddhant Kumar"
blogTitle: "testing web apps with cypress"
description: "testing web apps with cypress"
layout: layouts/post.njk
permalink: "/posts/{{ blogTitle | slug }}/"
tags: tests

eleventyNavigation:
  key: posts
  title: "testing web apps with cypress"
---

# My test post

## More posts in this series

{% for post in collections.tests %}
<a href="{{post.url}}">{{post.data.blogTitle}}</a>
{% endfor %}

In this post we will setup cypress and start writing tests

[code](https://www.github.com/siddhantk232)
