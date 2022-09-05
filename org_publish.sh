#!/usr/bin/env bash

emacs -Q --script org_publish.el

mv src/notes/theindex.html src/notes/index.html
