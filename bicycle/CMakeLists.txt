set(CMAKE_INSTALL_RPATH $ORIGIN)

set(Bicycle_INSTALL_CMAKEDIR
      ${CMAKE_ISNTALL_LIBDIR}/cmake/bicycle
      CACHE STRING "Path to bicycle cmake files")

include(GenerateExportHeader)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/bicycle-config.cmake.in
    bicycle-config.cmake
    INSTALL_DESTINATION ${Bicycle_INSTALL_CMAKEDIR}
)

write_basic_package_version_file(
    bicycle-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/bicycle-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/bicycle-config-version.cmake
    DESTINATION ${Bicycle_INSTALL_CMAKEDIR})

add_subdirectory(core)
# add_subdirectory(net)
