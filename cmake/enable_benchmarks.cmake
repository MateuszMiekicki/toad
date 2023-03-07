option(ENABLE_BENCHMARKS "Enable benchmarks" OFF)
if(ENABLE_BENCHMARKS)
  add_subdirectory(${CMAKE_SOURCE_DIR}/benchmarks)
endif()
