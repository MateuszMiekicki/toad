#!/bin/sh
for dir in cmake packages services; do
    find "$dir" \
         \( -name 'CMakeLists.txt' \
         -o -name '*.cmake' \) \
         -exec "cmake-format" --config-files .cmake-format -i '{}' \;
done
"cmake-format" --config-files .cmake-format -i CMakeLists.txt;
