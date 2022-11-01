for dir in . cmake packages; do
    find . \
         \( -name 'CMakeLists.txt' \
         -o -name '*.cmake' \) \
         -exec "cmake-format" --config-files .cmake-format -i '{}' \;
done