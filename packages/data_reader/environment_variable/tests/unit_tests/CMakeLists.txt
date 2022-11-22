project(unit_tests_${MODULE_NAME} LANGUAGES CXX)

find_package(GTest REQUIRED)
aux_source_directory(. SOURCE)
add_executable(${PROJECT_NAME}
        ${SOURCE}
        )
target_link_libraries(${PROJECT_NAME}
        PRIVATE GTest::gmock_main
        PRIVATE GTest::gtest_main
        PRIVATE GTest::gmock
        PRIVATE toad::data_reader::environment_variable::environment_variable::environment_variable
        )
target_include_directories(${PROJECT_NAME}
PRIVATE ${CMAKE_SOURCE_DIR}/include
PRIVATE ${gtest_SOURCE_DIR})
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
        )
target_compile_options(
  ${PROJECT_NAME}
  PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Release>:${GCC_FLAGS_RELEASE}>>
  PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Debug>:${GCC_FLAGS_DEBUG}>>)

gtest_discover_tests(${PROJECT_NAME}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)