find packages -type f \( -name "*.hh" -o -name "*.cc" \) \
   -exec clang-tidy -p build/ \
   --header-filter="include/" {} \;