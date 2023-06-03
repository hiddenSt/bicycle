add_library(executors)
add_library(bicycle::executors ALIAS executors)

#----------------------------------------------------------------------------------------------------------------------
# sources
#----------------------------------------------------------------------------------------------------------------------

set(sources
    include/bicycle/executors/detail/mpmc_blocking_queue.hpp
    include/bicycle/executors/executor.hpp
    include/bicycle/executors/export.h
    include/bicycle/executors/inline_executor.hpp
    include/bicycle/executors/manual_executor.hpp
    include/bicycle/executors/strand.hpp
    include/bicycle/executors/task.hpp
    include/bicycle/executors/thread_pool.hpp
    src/inline_executor.cpp
    src/manual_executor.cpp
    src/strand.cpp
    src/thread_pool.cpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sources})

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if (NOT BUILD_SHARED_LIBS)
  set(export_file_name "export_static.h")
endif()

generate_export_header(executors
        EXPORT_MACRO_NAME BICYCLE_EXPORT
        EXPORT_FILE_NAME include/bicycle/executors/${export_file_name}
)

target_sources(executors PRIVATE ${sources})

target_compile_definitions(executors PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:BICYCLE_STATIC_DEFINE>")

target_include_directories(executors
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

target_link_libraries(executors
  PRIVATE
    bicycle::core
  PUBLIC
    bicycle::container
)

set_target_properties(executors PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION})

if (BICYCLE_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
  install(TARGETS executors EXPORT executors-targets
          INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
          RUNTIME COMPONENT bicycle
          LIBRARY COMPONENT bicycle NAMELINK_COMPONENT bicycle-dev
          ARCHIVE COMPONENT bicycle-dev)

  set(targets_file "bicycle-executors-shared-targets.cmake")

  if (NOT BUILD_SHARED_LIBS)
    set(targets_file "bicycle-executors-static-targets.cmake")
  endif()

  install(EXPORT executors-targets
          DESTINATION ${BICYCLE_INSTALL_CMAKEDIR}
          NAMESPACE bicycle::
          FILE "${targets_file}"
          COMPONENT bicycle-dev)

  install(DIRECTORY
          ${CMAKE_CURRENT_SOURCE_DIR}/include
          TYPE INCLUDE)
endif()

enable_sanitizers(executors)

if (BUILD_TESTING)
  add_subdirectory(tests)
endif()