cmake_minimum_required(VERSION 3.21)

project(bicycle
        VERSION 0.0.1
        DESCRIPTION "Library contains common utilities for my pet projects"
        LANGUAGES CXX)

#---------------------------------------------------------------------------------------------------
# General settings and options
#---------------------------------------------------------------------------------------------------

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(GNUInstallDirs)
include(cmake/CompilerWarnings.cmake)
include(cmake/Utils.cmake)
include(cmake/Sanitizers.cmake)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(BICYCLE_BUILD_TESTS "Build bicycle tests" OFF)
option(BICYCLE_BUILD_DOCS "Build bicycle documentation" OFF)
option(BICYCLE_INSTALL "Generate target for installing bicycle" ${is_top_level})

set_if_undefined(
  ${BICYCLE_INSTALL_CMAKEDIR} "${CMAKE_INSTALL_LIBDIR}/cmake/bicycle"
  CACHE STRING  "Install path for bicycle package-related CMake files"
)

set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if (DEFINED BICYCLE_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ${BICYCLE_SHARED_LIBS})
endif()

if (NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake")
  include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)
endif()

# To be able to use std::format
# add_compile_options(-stdlib=libc++)

#---------------------------------------------------------------------------------------------------
# Project-wise install set
#---------------------------------------------------------------------------------------------------

if (BICYCLE_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
  include(CMakePackageConfigHelpers)

  configure_package_config_file(
    cmake/bicycleConfig.cmake.in
    bicycleConfig.cmake
    INSTALL_DESTINATION "${BICYCLE_INSTALL_CMAKEDIR}"
  )

  write_basic_package_version_file(
    bicycleConfigVersion.cmake
    COMPATIBILITY SameMajorVersion
  )

  install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/bicycleConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/bicycleConfigVersion.cmake"
    COMPONENT bicycle-dev
    DESTINATION "${BICYCLE_INSTALL_CMAKEDIR}"
  )
endif()

if (BICYCLE_BUILD_TESTS)
  include(CTest)
  include(third_party/Catch2.cmake)
endif()

#---------------------------------------------------------------------------------------------------
# Library components
#---------------------------------------------------------------------------------------------------

add_subdirectory(core)

#---------------------------------------------------------------------------------------------------
# Library docs
#---------------------------------------------------------------------------------------------------

if (BICYCLE_BUILD_DOCS)
  add_subdirectory(docs)
endif()


