cmake_minimum_required(VERSION 3.20)
project(executor-tests)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)
include(../../third_party/Catch2.cmake)

#----------------------------------------------------------------------------------------------------------------------
# dependencies
#----------------------------------------------------------------------------------------------------------------------

if (is_top_level)
  find_package(bicycle 1.0.0 REQUIRED COMPONENTS container)
endif()

#----------------------------------------------------------------------------------------------------------------------
# sources
#----------------------------------------------------------------------------------------------------------------------

set(sources intrusive_linked_list_tests.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# tests target
#----------------------------------------------------------------------------------------------------------------------

add_executable(container-tests)
target_sources(container-tests PRIVATE ${sources})
enable_sanitizers(container-tests)

target_link_libraries(container-tests
  PRIVATE
    Catch2::Catch2WithMain
    bicycle::container
)

include(Catch)
catch_discover_tests(container-tests)