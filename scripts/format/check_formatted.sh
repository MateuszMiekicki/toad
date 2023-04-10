#!/bin/sh
status=$(git status --porcelain)
if [ -n "$status" ]; then
  echo "Correct the formatting in the files belowe";
  echo "$status"
  exit 1;
else
  echo "Formatting correct";
  exit 0;
fi