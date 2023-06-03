cmake_minimum_required(VERSION 3.20)
project(allocator-tests)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)
include(../../third_party/Catch2.cmake)

#----------------------------------------------------------------------------------------------------------------------
# dependencies
#----------------------------------------------------------------------------------------------------------------------

if (is_top_level)
  find_package(bicycle 1.0.0 REQUIRED COMPONENTS allocator)
endif()

#----------------------------------------------------------------------------------------------------------------------
# sources
#----------------------------------------------------------------------------------------------------------------------

set(sources mmap_allocator_tests.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# tests target
#----------------------------------------------------------------------------------------------------------------------

add_executable(allocator-tests)
target_sources(allocator-tests PRIVATE ${sources})
enable_sanitizers(allocator-tests)

target_link_libraries(allocator-tests
  PRIVATE
    Catch2::Catch2WithMain
    bicycle::allocator
)

include(Catch)
catch_discover_tests(allocator-tests)