add_library(future)
add_library(bicycle::future ALIAS future)

set(sources
  include/bicycle/future.hpp
  src/detail.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})
target_sources(future PRIVATE ${sources})