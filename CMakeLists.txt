cmake_minimum_required(3.19)

project(bicycle
        VERSION 0.0.1
        DESCRIPTION "Library contains common utilities for my pet projects"
        LANGUAGES CXX)

include(cmake/Sanitizers.cmake)
include(CTest)

if (TESTING_ENABLED)
  add_subdirectory(test)
  add_subdirectory(fuzz_test)
endif()
