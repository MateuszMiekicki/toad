option(USE_CLANG_TIDY "If ON code inspection is performed during build" ON)

macro(use_clang_tidy)
  if(${USE_CLANG_TIDY})
    set(CMAKE_CXX_CLANG_TIDY
        clang-tidy --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy
        -header-filter=${CMAKE_CURRENT_SOURCE_DIR}/../include/toad --extra-arg=-Wno-unknown-warning-option)
  endif()
endmacro()
