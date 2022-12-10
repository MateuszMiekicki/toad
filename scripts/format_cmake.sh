for dir in cmake packages services; do
    find . \
         \( -name 'CMakeLists.txt' \
         -o -name '*.cmake' \) \
         -exec "cmake-format" --config-files .cmake-format -i '{}' \;
done
exec "cmake-format" --config-files .cmake-format -i CMakeLists.txt;
