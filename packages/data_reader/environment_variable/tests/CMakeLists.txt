option(ENABLE_UNIT_TESTS "Enable unit tests" ON)
if (ENABLE_UNIT_TESTS)
    add_subdirectory(unit_tests)
endif ()