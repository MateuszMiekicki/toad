option(ENABLE_EXAMPLES "Enable examples" OFF)
if(ENABLE_EXAMPLES)
  add_subdirectory(${CMAKE_SOURCE_DIR}/examples)
endif()
