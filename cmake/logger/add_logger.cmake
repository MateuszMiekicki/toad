function(add_logger project_name)

  find_package(spdlog QUIET REQUIRED)
  find_package(fmt QUIET REQUIRED)
  configure_file("${CMAKE_SOURCE_DIR}/cmake/logger/Logger.hh.in"
                 "${CMAKE_CURRENT_SOURCE_DIR}/../include/toad/${PACKAGE_NAME}/${COMPONENT_NAME}/Logger.hh")
  target_link_libraries(${project_name} PUBLIC spdlog::spdlog)
  target_link_libraries(${project_name} PUBLIC fmt::fmt)
endfunction()
