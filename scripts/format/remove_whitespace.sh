#!/bin/sh
find . -not \( -name .svn -prune -o -name .git -prune \) -type f -print0 | perl -0ne 'print if -T' | xargs -0 sed -Ei 's/[[:blank:]]+$//'