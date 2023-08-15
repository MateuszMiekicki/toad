include(FetchContent)
FetchContent_Declare(
  questdb
  GIT_REPOSITORY https://github.com/questdb/c-questdb-client.git
  GIT_TAG 2.1.3)
FetchContent_GetProperties(questdb)
if(NOT questdb_POPULATED)
  FetchContent_Populate(questdb)
  add_subdirectory(${questdb_SOURCE_DIR} ${questdb_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
