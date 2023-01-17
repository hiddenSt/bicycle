add_executable(core_tests observer_ptr_test.cpp)
target_link_libraries(core_tests PRIVATE bicycle::core Catch2::Catch2)
target_include_directories(core_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})