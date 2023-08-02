cmake_minimum_required(VERSION 3.22)
project(
  toad
  VERSION 0.1.0
  LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")

set(BUILD_SHARED_LIBS OFF)
function(get_git_commit_hash GIT_COMMIT_HASH)
  execute_process(
    COMMAND git rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE ${GIT_COMMIT_HASH}
    OUTPUT_STRIP_TRAILING_WHITESPACE)
endfunction()

get_git_commit_hash(CURRENT_COMMIT_HASH)
string(TIMESTAMP BUILD_TIME "%Y-%m-%dT%H:%M:%SZ" UTC)
set(CURRENT_VERSION
    "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-${CURRENT_COMMIT_HASH}-${BUILD_TIME}")
message(STATUS "version: ${CURRENT_VERSION}")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_DEBUG_POSTFIX "-debug")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
  message(WARNING "Set default build type: ${CMAKE_BUILD_TYPE}")
elseif(CMAKE_BUILD_TYPE MATCHES "Release")
  set(CMAKE_BUILD_TYPE Release)
elseif(CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

include(gcc_flags)
include(enable_code_coverage)
include(use_sanitizer)
include(enable_tests)
include(logger/add_logger)

include(fetch_content/c-questdb-client)

# include(enable_docs) include(enable_benchmarks) include(enable_examples) add_subdirectory(packages/data_reader)

add_subdirectory(packages/communication_protocol)
add_subdirectory(packages/storage)

add_subdirectory(services)
