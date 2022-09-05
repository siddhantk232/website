#!/usr/bin/env bash

# TODO fix publishing from command line
# emacs -Q --script org_publish.el

mv src/notes/theindex.html src/notes/index.html

changed_files=`git status --short | awk '{print $2}'`

read -r -d '' commit_message << EOM
updated notes:

${changed_files}
EOM


git add .
git commit -m "$commit_message"
git push
