option(ENABLE_BENCHMARKS "Enable benchmarks" ON)
if (ENABLE_BENCHMARKS)
    add_subdirectory(${CMAKE_SOURCE_DIR}/benchmarks)
endif ()