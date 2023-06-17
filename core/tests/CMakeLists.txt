cmake_minimum_required(VERSION 3.20)
project(core-tests)

#----------------------------------------------------------------------------------------------------------------------
# general settings and options
#----------------------------------------------------------------------------------------------------------------------

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

#----------------------------------------------------------------------------------------------------------------------
# dependencies
#----------------------------------------------------------------------------------------------------------------------

if (is_top_level)
  find_package(bicycle 1.0.0 REQUIRED COMPONENTS core)
endif()

#----------------------------------------------------------------------------------------------------------------------
# sources
#----------------------------------------------------------------------------------------------------------------------

set(sources observer_ptr_tests.cpp result_tests.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

#----------------------------------------------------------------------------------------------------------------------
# tests target
#----------------------------------------------------------------------------------------------------------------------

add_executable(core-tests)
target_sources(core-tests PRIVATE ${sources})
enable_sanitizers(core-tests)

target_link_libraries(core-tests
  PRIVATE
    Catch2::Catch2WithMain
    bicycle::core
)

include(Catch)
catch_discover_tests(core-tests)