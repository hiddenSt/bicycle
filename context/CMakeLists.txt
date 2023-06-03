add_library(context)
add_library(bicycle::context ALIAS context)

target_sources(context
  PRIVATE
    include/bicycle/context/context.hpp
    include/bicycle/context/trampoline.hpp)

target_include_directories(context
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_subdirectory(src)