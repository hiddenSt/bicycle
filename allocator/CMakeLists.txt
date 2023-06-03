add_library(allocator)
add_library(bicycle::allocator ALIAS allocator)

#----------------------------------------------------------------------------------------------------------------------
# sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if (NOT BUILD_SHARED_LIBS)
  set(export_file_name "export_static.h")
endif()

generate_export_header(allocator
  EXPORT_MACRO_NAME BICYCLE_EXPORT
  EXPORT_FILE_NAME include/bicycle/allocator/${export_file_name}
)

target_sources(allocator
  PRIVATE
    include/bicycle/allocator/export.h
        include/bicycle/allocator/mmap_allocation.hpp
        src/mmap_allocation.cpp
)

target_compile_definitions(allocator PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:BICYCLE_STATIC_DEFINE>")

target_include_directories(allocator
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

target_link_libraries(allocator PRIVATE bicycle::core)

set_target_properties(allocator PROPERTIES
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION ${PROJECT_VERSION})

set_target_warnings(allocator
  "${BICYCLE_WARNINGS_AS_ERRORS}"
  "${BICYCLE_CLANG_WARNINGS}"
  "${BICYCLE_GCC_WARNINGS}")

#----------------------------------------------------------------------------------------------------------------------
# install set
#----------------------------------------------------------------------------------------------------------------------

if (BICYCLE_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
  install(TARGETS allocator EXPORT allocator-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    RUNTIME COMPONENT bicycle
    LIBRARY COMPONENT bicycle NAMELINK_COMPONENT bicycle-dev
    ARCHIVE COMPONENT bicycle-dev
  )

  set(targets_file "bicycle-allocator-shared-targets.cmake")

  if (NOT BUILD_SHARED_LIBS)
    set(targets_file "bicycle-allocator-static-targets.cmake")
  endif()

  install(EXPORT allocator-targets
    DESTINATION ${BICYCLE_INSTALL_CMAKEDIR}
    NAMESPACE bicycle::
    FILE "${targets_file}"
    COMPONENT bicycle-dev)

  install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    TYPE INCLUDE
  )
endif()

enable_sanitizers(allocator)

#----------------------------------------------------------------------------------------------------------------------
# tests
#----------------------------------------------------------------------------------------------------------------------

if (BUILD_TESTING)
  add_subdirectory(tests)
endif()
