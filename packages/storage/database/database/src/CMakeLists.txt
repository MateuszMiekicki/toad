project(
  database_interface
  VERSION 0.1.0
  LANGUAGES CXX)

add_library(${PROJECT_NAME} INTERFACE )
add_library(${CMAKE_PROJECT_NAME}::${PACKAGE_NAME}::${COMPONENT_NAME}::${MODULE_NAME}::${PROJECT_NAME} ALIAS
            ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../include/)