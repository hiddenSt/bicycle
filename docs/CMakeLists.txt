cmake_minimum_required(VERSION 3.20)
project(bicycle-docs)

#----------------------------------------------------------------------------------------------------------------------
# dependencies
#----------------------------------------------------------------------------------------------------------------------

find_package(Doxygen REQUIRED)
find_package(Sphinx REQUIRED)

#----------------------------------------------------------------------------------------------------------------------
# general settings
#----------------------------------------------------------------------------------------------------------------------

set(BICYCLE_PUBLIC_HEADER_DIRS "")
# get_target_property(BICYCLE_CORE_PUBLIC_HEADER_DIR bicycle::core INTERFACE_INCLUDE_DIRECTORIES)
# file(GLOB_RECURSE BICYCLE_PUBLIC_HEADERS ${BICYCLE_CORE_PUBLIC_HEADER_DIR}/*.hpp)

set(DOXYGEN_INPUT_DIR "${PROJECT_ROOT_DIR}/core/include/bicycle/core")
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT})

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
  # DEPENDS ${BICYCLE_PUBLIC_HEADERS}
  COMMAND ${DOXYGEN_EXECUTABLE}
  MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
  COMMENT "Generating docs"
  VERBATIM)

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
  COMMAND
    ${SPHINX_EXECUTABLE} -b html
    -Dbreathe_projects.bicycle=${DOXYGEN_OUTPUT_DIR}/xml
    ${SPHINX_SOURCE} ${SPHINX_BUILD}
  WORKING_DIRECTORY
    ${CMAKE_CURRENT_BINARY_DIR}
  DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/index.rst
    ${DOXYGEN_INDEX_FILE}
  MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
  COMMENT "Generating documentation for bicycle")
add_custom_target(docs ALL DEPENDS ${SPHINX_INDEX_FILE})

install(DIRECTORY ${SPHINX_BUILD}
        DESTINATION ${CMAKE_INSTALL_DOCDIR})
