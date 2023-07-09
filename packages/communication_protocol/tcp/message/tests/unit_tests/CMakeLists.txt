project(${MODULE_NAME}_ut LANGUAGES CXX)
find_package(GTest 1.13 QUIET REQUIRED)
include(GoogleTest)
aux_source_directory(. SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE GTest::gtest
  PRIVATE GTest::gtest_main
  PRIVATE GTest::gmock
  PRIVATE GTest::gmock_main
  PRIVATE toad::communication_protocol::tcp::message)
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
             CXX_STANDARD 17
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON)

# gtest_discover_tests(${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
