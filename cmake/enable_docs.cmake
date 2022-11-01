option(ENABLE_DOCS "Enabling the generation of documentation" ON)
if(ENABLE_DOCS)
  add_subdirectory(${CMAKE_SOURCE_DIR}/docs)
endif()
