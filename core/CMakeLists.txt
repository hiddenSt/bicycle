add_library(core)
add_library(bicycle::core ALIAS core)

#----------------------------------------------------------------------------------------------------------------------
# targets and sources
#----------------------------------------------------------------------------------------------------------------------

include(GenerateExportHeader)
set(export_file_name "export_shared.h")

if (NOT BUILD_SHARED_LIBS)
  set(export_file_name "export_static.h")
endif()

generate_export_header(core
  EXPORT_MACRO_NAME BICYCLE_EXPORT
  EXPORT_FILE_NAME include/bicycle/core/${export_file_name}
)

target_sources(core
  PRIVATE
    include/bicycle/core/export.h
    include/bicycle/core/contracts.hpp
    include/bicycle/core/result.hpp
    include/bicycle/core/observer_ptr.hpp
    src/contracts.cpp)

target_compile_definitions(core PUBLIC "$<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:BICYCLE_STATIC_DEFINE>")

target_include_directories(core
  PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>")

set_target_properties(core PROPERTIES
  SOVERSION ${PROJECT_VERSION_MAJOR}
  VERSION ${PROJECT_VERSION})

set_target_warnings(core
  "${BICYCLE_WARNINGS_AS_ERRORS}"
  "${BICYCLE_CLANG_WARNINGS}"
  "${BICYCLE_GCC_WARNINGS}")

#----------------------------------------------------------------------------------------------------------------------
# install set
#----------------------------------------------------------------------------------------------------------------------

if (BICYCLE_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
  install(TARGETS core EXPORT core-targets
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    RUNTIME COMPONENT bicycle
    LIBRARY COMPONENT bicycle NAMELINK_COMPONENT bicycle-dev
    ARCHIVE COMPONENT bicycle-dev)

  set(targets_file "bicycle-core-shared-targets.cmake")

  if (NOT BUILD_SHARED_LIBS)
    set(targets_file "bicycle-core-static-targets.cmake")
  endif()

  install(EXPORT core-targets
    DESTINATION ${BICYCLE_INSTALL_CMAKEDIR}
    NAMESPACE bicycle::
    FILE "${targets_file}"
    COMPONENT bicycle-dev)

  install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    TYPE INCLUDE
    COMPONENT bicycle-dev)
endif()

enable_sanitizers(core)

#----------------------------------------------------------------------------------------------------------------------
# tests
#----------------------------------------------------------------------------------------------------------------------

if (BICYCLE_BUILD_TESTS)
  add_subdirectory(tests)
endif()
