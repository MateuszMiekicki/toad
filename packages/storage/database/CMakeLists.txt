set(COMPONENT_NAME "database")

add_subdirectory(questdb)
add_subdirectory(entities)

project(
  ${COMPONENT_NAME}
  VERSION 0.1.0
  LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${CMAKE_PROJECT_NAME}::${PACKAGE_NAME}::${COMPONENT_NAME} ALIAS ${PROJECT_NAME})
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES VERSION ${PROJECT_VERSION}
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "${PACKAGE_NAME}-${PROJECT_NAME}"
             ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
             CXX_STANDARD 17
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON)
target_link_libraries(
  ${PROJECT_NAME}
  INTERFACE toad::storage::database::questdb
  INTERFACE toad::storage::database::entities)
