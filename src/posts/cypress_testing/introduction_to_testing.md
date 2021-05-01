---
title: "Introduction - testing websites with cypress"
date: "2020-08-06"
description: "javascript testing series with cypress. In this series we will use cypress for end-to-end testing of our websites. We will also learn how to test react apps with cypress"
layout: layouts/post.njk
permalink: "/posts/{{ title | slug }}/"
canonical: "/posts/introduction-testing-websites-with-cypress"
cssclass: "post-container"
tags:
  - posts
  - cypress
  - testing_js
---

# Basics of software testing.

**software testing**, in simple words, is the process of testing your application against specified conditions.

This can be done manually or using some automated tools.

> In this blog series we will be **focusing on automating our tests** as we usually do manual testing while building our app. Also, we will write tests for web applications. If you are looking for testing your Java app or something else then the coming blogs in this series might not be for you but you can still read this part.

## why testing?

- Testing you software is important because there can be bugs which can ruin whole experience of your app. While doing manual testing we sometimes miss those edge cases which our users won't.

- Testing our apps can save us money as we will know which features work before shipping our product to the customers. So, we can tell them before trying that this part may not work in this condition. This establishes a better customer relationship.

- Following test-driven-development also reduces complexity that we face while building the app as we are already writing the tests for the code we are going to write.

- In an agile environment where you have to ship product as we develop, testing can save us huge time.

## Types of tests.

There are many types of tests and testing strategies. Listed below are enough for begineers, you can always learn about new strategies on the go :)

### Unit tests

This approach is followed for testing one unit of your codebase at a time. For example, you can test a function which takes two strings and joins them with a space. writing test for this kind of function is easy as if you provide 'hello' and 'world' then you'd expect it to return 'hello world'. This is called unit testing.

Unit tests are the easiest to write and test.

### integration tests or end-to-end (e2e) tests:

This is similar to manual testing. In this process your automation tools starts your application and goes through each step that you'd do manually and checks if they pass or fail.

They are relatively hard to configure and describe.

## Summary

In this blog we learned about what is software testing, why it is important and some comman testing strategies.

In the next blog in this series, we will learn about cypress which is a end-to-end testing framework for testing javscript application.
