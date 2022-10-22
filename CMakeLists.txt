cmake_minimum_required(VERSION 3.22)
project(honeybadger VERSION 0.1.0 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

string(TIMESTAMP BUILD_TIME "%Y-%m-%d")
set(CURRENT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-${BUILD_TIME}")
message(STATUS "version: ${CURRENT_VERSION}")
option(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_DEBUG_POSTFIX "-debug")


if(NOT CMAKE_BUILD_TYPE)
    message(WARNING "Available build types: Debug or Release.")
    SET(CMAKE_BUILD_TYPE Debug)
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
    set(CMAKE_BUILD_TYPE Release)
elseif (CMAKE_BUILD_TYPE MATCHES "RelWithDebInfo")
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif ()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

include(enable_code_coverage)
include(use_clang_tidy)
include(use_sanitizer)
include(enable_tests)

# include(enable_docs)
#include(enable_benchmarks)
#include(enable_examples)


add_subdirectory(packages/security)

#add_subdirectory(server)



