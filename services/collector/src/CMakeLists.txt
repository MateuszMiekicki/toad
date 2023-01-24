project(
  ${SERVICE_NAME}
  VERSION 0.1.0
  LANGUAGES CXX)

aux_source_directory(. SOURCE)
add_executable(${PROJECT_NAME} ${SOURCE})
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES VERSION ${PROJECT_VERSION}
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "${PROJECT_NAME}"
             ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
             CXX_STANDARD 17
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_link_libraries(${PROJECT_NAME} PRIVATE toad::network::network)
target_link_libraries(${PROJECT_NAME} PRIVATE toad::broker::broker)

find_package(mqtt_cpp_iface 13 REQUIRED)
find_package(OpenSSL REQUIRED)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE mqtt_cpp_iface::mqtt_cpp_iface
  PRIVATE OpenSSL::Crypto
  PRIVATE OpenSSL::SSL)
target_link_libraries(${PROJECT_NAME} PRIVATE $<$<BOOL:${WIN32}>:ws2_32>)

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Release>:${GCC_FLAGS_RELEASE}>>
  PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Debug>:${GCC_FLAGS_DEBUG}>>)
