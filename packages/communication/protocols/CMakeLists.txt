set(PACKAGE_NAME "${PACKAGE_NAME}::protocols")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/publish_subscribe)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/types)
