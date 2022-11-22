function(add_logger project_name)
  configure_file("${CMAKE_SOURCE_DIR}/cmake/logger/Logger.hh.in"
                 "${CMAKE_CURRENT_SOURCE_DIR}/../include/toad/Logger.hh")

  configure_file("${CMAKE_SOURCE_DIR}/cmake/logger/Logger.cc.in" "${CMAKE_CURRENT_SOURCE_DIR}/../src/Logger.cc")
  target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)
endfunction()
