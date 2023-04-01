#!/bin/sh
find packages -type f \( -name "*.hh" -o -name "*.cc" \) \
   -exec clang-tidy -p build/ \
   -extra-arg=-Wno-unknown-warning-option {} \;