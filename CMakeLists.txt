cmake_minimum_required(VERSION 3.22)
project(
  toad
  VERSION 0.1.0
  LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR}")

set(BUILD_SHARED_LIBS ON)
string(TIMESTAMP BUILD_TIME "%Y-%m-%d")
set(CURRENT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}-${BUILD_TIME}")
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

# include(enable_docs) include(enable_benchmarks) include(enable_examples) add_subdirectory(packages/data_reader)

add_subdirectory(packages/server)
add_subdirectory(packages/broker)

add_subdirectory(services/collector)

# # app------------------ find_package(mqtt_cpp REQUIRED) find_package(spdlog REQUIRED) find_package(SOCI REQUIRED)
# find_package(gtest REQUIRED) find_package(yaml-cpp REQUIRED) add_executable(${CMAKE_PROJECT_NAME} app/main.cc)
# set_target_properties( ${CMAKE_PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR}
# ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/ LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/
# RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CXX_STANDARD 17 CXX_EXTENSIONS OFF CXX_STANDARD_REQUIRED ON)
# target_link_libraries(${CMAKE_PROJECT_NAME} mqtt_cpp::mqtt_cpp)

# target_compile_options( ${CMAKE_PROJECT_NAME} PRIVATE
# $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Release>:${GCC_FLAGS_RELEASE}>> PRIVATE
# $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Debug>:${GCC_FLAGS_DEBUG}>>)
