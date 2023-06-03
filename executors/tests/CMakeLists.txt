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
  find_package(bicycle 1.0.0 REQUIRED COMPONENTS executors)
endif()

#----------------------------------------------------------------------------------------------------------------------
# sources
#----------------------------------------------------------------------------------------------------------------------

set(sources manual_executor_tests.cpp thread_pool_tests.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# tests target
#----------------------------------------------------------------------------------------------------------------------

add_executable(executors-tests)
target_sources(executors-tests PRIVATE ${sources})
enable_sanitizers(executors-tests)

target_link_libraries(executors-tests
        PRIVATE
        Catch2::Catch2WithMain
        bicycle::executors
        )

include(Catch)
catch_discover_tests(executors-tests)