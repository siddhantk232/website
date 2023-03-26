#!/usr/bin/env bash

emacs -Q --script org_publish.el

mv src/notes/theindex.html src/notes/index.html

read -r -d '' commit_message << EOM
exported notes
EOM

git add .
git commit -m "$commit_message"
git push
