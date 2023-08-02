include(FetchContent)
FetchContent_Declare(
  questdb
  GIT_REPOSITORY https://github.com/questdb/c-questdb-client.git
  GIT_TAG 2.1.3)
FetchContent_MakeAvailable(questdb)
