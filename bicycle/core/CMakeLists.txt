add_library(core)
add_library(bicycle::core ALIAS core)

generate_export_header(core)

target_sources(core
    PRIVATE
      include/bicycle/contract.hpp
      include/bicycle/result.hpp
      include/bicycle/observer_ptr.hpp
      src/contract.cpp
)

target_include_directories(core
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<BUILD_INTERFACE:${CMAKE_CURRENT_BUILD_BINARY_DIR}>
)

set_target_properties(core PROPERTIES
    SOVERSION ${PROJECT_VERSION_MAJOR}
    VERSION ${PROJECT_VERSION})

install(TARGETS core 
        EXPORT core-targets
        INCLUDES DESTINTION ${CMAKE_INSTALL_INCLUDEDIR}
        RUNTIME COMPONENT BicycleCore_Runtime
        LIBRARY COMPONENT BicycleCore_Runtime
                NAMELINK_COMPONENT BicycleCore_Development
        ARCHIVE COMPONENT BicycleCore_Development
)

install(EXPORT core-targets
        DESTINATION ${Bicycle_INSTALL_CMAKEDIR}
        NAMESPACE bicycle::
        FILE bicycle-targets.cmake
        COMPONENT BicycleCore_Development)

set_target_properties(core PROPERTIES
    EXPORT_NAME core)

install(DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    TYPE INCLUDE)
