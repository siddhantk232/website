---
title: "Testing 101 | Siddhant Kumar"
blogTitle: "Testing 101"
description: "Testing 101"
layout: layouts/post.njk
permalink: "/posts/{{ title | slug }}/"
tags: tests

eleventyNavigation:
  key: posts
  title: "Testing 101"
---

# My test post

## More posts in this series

{% for post in collections.tests %}
<a href="{{post.url}}">{{post.data.blogTitle}}</a>
{% endfor %}

### TODO:

1. Say hi
2. Say by
