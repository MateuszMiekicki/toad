if [ -n "$(git status --porcelain)" ]; then
  echo "Correct the formatting in the files above";
  exit 1;
else
  echo "Formatting correct";
  exit 0;
fi