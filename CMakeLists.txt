cmake_minimum_required(VERSION 3.19)

project(bicycle
        VERSION 0.0.1
        DESCRIPTION "Library contains common utilities for my pet projects"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(GNUInstallDirs)
include(cmake/Sanitizers.cmake)
include(CTest)

add_subdirectory(bicycle)

if (TESTING_ENABLED)
  add_subdirectory(test)
  add_subdirectory(fuzz_test)
endif()
