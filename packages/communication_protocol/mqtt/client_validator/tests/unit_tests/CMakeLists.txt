project(${MODULE_NAME}_ut LANGUAGES CXX)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})

set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
             CXX_STANDARD 17
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON)

find_package(GTest 1.13 QUIET REQUIRED)
include(GoogleTest)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE GTest::gtest
  PRIVATE GTest::gtest_main
  PRIVATE GTest::gmock
  PRIVATE GTest::gmock_main)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  PRIVATE toad::communication_protocol::mqtt::client_validator)

gtest_discover_tests(${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
