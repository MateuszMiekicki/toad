project(
  ${MODULE_NAME}
  VERSION 0.1.0
  LANGUAGES CXX)

use_clang_tidy()

find_package(spdlog REQUIRED)
aux_source_directory(. SOURCE)
add_library(${PROJECT_NAME} ${SOURCE})
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES VERSION ${PROJECT_VERSION}
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "${PACKAGE_NAME}-${PROJECT_NAME}"
             ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib/
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
             CXX_STANDARD 17
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON)
add_library(${CMAKE_PROJECT_NAME}::${PACKAGE_NAME}::${COMPONENT_NAME}::${MODULE_NAME}::${PROJECT_NAME} ALIAS
            ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_logger(${MODULE_NAME})
target_compile_options(
  ${PROJECT_NAME}
  PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Release>:${GCC_FLAGS_RELEASE}>>
  PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Debug>:${GCC_FLAGS_DEBUG}>>)
