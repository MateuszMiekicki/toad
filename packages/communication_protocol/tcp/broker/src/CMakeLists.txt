project(
  ${MODULE_NAME}
  VERSION 0.1.0
  LANGUAGES CXX)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SOURCE)
add_library(${PROJECT_NAME} ${SOURCE})
add_library(${CMAKE_PROJECT_NAME}::${PACKAGE_NAME}::${COMPONENT_NAME}::${MODULE_NAME} ALIAS ${PROJECT_NAME})
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES VERSION ${PROJECT_VERSION}
             SOVERSION ${PROJECT_VERSION_MAJOR}
             OUTPUT_NAME "${PACKAGE_NAME}-${COMPONENT_NAME}-${MODULE_NAME}"
             ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
             CXX_STANDARD 17
             CXX_EXTENSIONS OFF
             CXX_STANDARD_REQUIRED ON)

add_logger(${PROJECT_NAME})
find_package(OpenSSL QUIET REQUIRED)
find_package(RapidJSON REQUIRED)
target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE OpenSSL::Crypto
  PRIVATE OpenSSL::SSL)
target_link_libraries(${PROJECT_NAME} PRIVATE $<$<BOOL:${WIN32}>:ws2_32>)
target_link_libraries(${PROJECT_NAME} PUBLIC toad::communication_protocol::network::endpoint)
target_link_libraries(${PROJECT_NAME} PUBLIC toad::communication_protocol::tcp::message)
target_link_libraries(${PROJECT_NAME} PRIVATE RapidJSON::RapidJSON)

find_package(Boost QUIET REQUIRED COMPONENTS system)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_compile_options(
  ${PROJECT_NAME}
  PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Release>:${GCC_FLAGS_RELEASE}>>
  PRIVATE $<$<CXX_COMPILER_ID:CXX,GNU>:$<$<CONFIG:Debug>:${GCC_FLAGS_DEBUG}>>)
