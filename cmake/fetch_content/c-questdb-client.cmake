include(FetchContent)
FetchContent_Declare(
  questdb
  GIT_REPOSITORY https://github.com/questdb/c-questdb-client.git
  GIT_TAG        2.1.3
)
FetchContent_MakeAvailable(questdb)

#FetchContent_GetProperties(questdb)
#if(NOT questdb_POPULATED)
#  FetchContent_Populate(questdb)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#             set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#             set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(BUILD_SHARED_LIBS ON)
#message(STATUS "kurwa ${questdb_SOURCE_DIR} kurwa ${questdb_BINARY_DIR}")
#  add_subdirectory(${questdb_SOURCE_DIR} ${questdb_BINARY_DIR})
#endif()