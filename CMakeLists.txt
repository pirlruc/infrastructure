cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

if(NOT DEFINED IMPROC_SUPERPROJECT_VERSION)
  set(IMPROC_SUPERPROJECT_VERSION 1.0.0)
endif()

if(NOT DEFINED IMPROC_INFRASTRUCTURE_WITH_TESTS)
  set(IMPROC_INFRASTRUCTURE_WITH_TESTS OFF)
endif()

if(IMPROC_WITH_TESTS OR IMPROC_INFRASTRUCTURE_WITH_TESTS)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

project(
  improc_infrastructure
  VERSION     ${IMPROC_SUPERPROJECT_VERSION}
  LANGUAGES   CXX
)

include(FetchContent)

# Project configuration
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Archive output dir.")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"      CACHE PATH "Library output dir.")
  set(CMAKE_PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "PDB (MSVC debug symbol)output dir.")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"      CACHE PATH "Executable/dll output dir.")
  set(CMAKE_DEBUG_POSTFIX d)
  option(IMPROC_WITH_TESTS 			     "Building library with tests"          OFF)
  option(IMPROC_WITH_COVERAGE  	     "Building library with code coverage"  OFF)
  option(BUILD_SHARED_LIBS           "Building shared libraries"            ON)
endif()

# Add external dependencies
# SPDLOG
if(DEFINED CMAKE_TOOLCHAIN_FILE)
  find_package(spdlog CONFIG REQUIRED)
else()
  FetchContent_Declare(
    spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog
    GIT_TAG         v1.12.0
    SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/spdlog
  )
  set(SPDLOG_MASTER_PROJECT ON)
  FetchContent_MakeAvailable(spdlog)
  target_include_directories(spdlog INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/spdlog/include>
                                              $<INSTALL_INTERFACE:include> )
  add_library(spdlog::spdlog ALIAS spdlog)
endif()

# JSONCPP
if(DEFINED CMAKE_TOOLCHAIN_FILE)
  find_package(jsoncpp CONFIG REQUIRED)
else()
  FetchContent_Declare(
    jsoncpp
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp
    GIT_TAG        1.9.5
    SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/jsoncpp
  )
  set(JSONCPP_WITH_TESTS    OFF)
  set(JSONCPP_WITH_EXAMPLE  OFF)
  set(BUILD_STATIC_LIBS     OFF)
  FetchContent_MakeAvailable(jsoncpp)
  add_library(JsonCpp::JsonCpp ALIAS jsoncpp_lib)
endif()

message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "CMake Toolchain File: ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")
message(STATUS "Install Dir: ${CMAKE_INSTALL_PREFIX}")

set(
  IMPROC_INFRASTRUCTURE_LIB_FILES

  ${PROJECT_SOURCE_DIR}/include/improc/exception.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/improc_defs.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/improc_type_traits.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/improc_function_traits.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/string.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/benchmark/benchmark_singleton.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/benchmark/benchmark_singleton.tpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/context/application_context.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/context/environment_context.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/context/environment_context.tpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/filesystem/file.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/filesystem/folder_policies.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/filesystem/folder_policies.tpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/filesystem/folder.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logging/logger_infrastructure.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logging/logger_singleton.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logging/logger_singleton.tpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/math/math.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/math/math.tpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/parsers/json_parser.hpp
  ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/parsers/json_parser.tpp
  
  ${PROJECT_SOURCE_DIR}/src/application_context.cpp
  ${PROJECT_SOURCE_DIR}/src/file.cpp
  ${PROJECT_SOURCE_DIR}/src/folder.cpp
  ${PROJECT_SOURCE_DIR}/src/string.cpp
)

add_library(${PROJECT_NAME} SHARED ${IMPROC_INFRASTRUCTURE_LIB_FILES})
add_library(improc::infrastructure ALIAS ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} spdlog::spdlog JsonCpp::JsonCpp)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD           17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE        CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION                ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})

target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                               $<INSTALL_INTERFACE:include> )

# Link dependencies
target_link_libraries       (${PROJECT_NAME}   PRIVATE   spdlog::spdlog)
target_link_libraries       (${PROJECT_NAME}   PRIVATE   JsonCpp::JsonCpp)
target_link_libraries       (${PROJECT_NAME}   INTERFACE spdlog::spdlog)
target_link_libraries       (${PROJECT_NAME}   INTERFACE JsonCpp::JsonCpp)

# Tests configuration
if(IMPROC_WITH_TESTS OR IMPROC_INFRASTRUCTURE_WITH_TESTS)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test     ${CMAKE_BINARY_DIR}/improc_infrastructure_test)
endif()

# Install configuration
if (NOT DEFINED CMAKE_INSTALL_LIBDIR)
  set(CMAKE_INSTALL_LIBDIR "lib")
endif()
if (NOT DEFINED CMAKE_INSTALL_BINDIR)
  set(CMAKE_INSTALL_BINDIR "bin")
endif()
if (NOT DEFINED CMAKE_INSTALL_INCLUDEDIR)
  set(CMAKE_INSTALL_INCLUDEDIR "include")
endif()

# Include files
set(IMPROC_INFRASTRUCTURE_TARGETS ${PROJECT_NAME})
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  list(APPEND IMPROC_INFRASTRUCTURE_TARGETS spdlog)
endif()

install(
  TARGETS     ${IMPROC_INFRASTRUCTURE_TARGETS}
  EXPORT      ${PROJECT_NAME}_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/improc                  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES   ${PROJECT_SOURCE_DIR}/external/jsoncpp/LICENSE          DESTINATION share/licenses/improc/jsoncpp)
install(FILES   ${PROJECT_SOURCE_DIR}/external/spdlog/LICENSE           DESTINATION share/licenses/improc/spdlog)
install(FILES   ${PROJECT_SOURCE_DIR}/LICENSE                           DESTINATION share/licenses/improc/infrastructure)

# pkg-config files
if(IS_ABSOLUTE ${CMAKE_INSTALL_INCLUDEDIR})
  set(PKG_CONFIG_INCLUDEDIR ${CMAKE_INSTALL_INCLUDEDIR})
else()
  set(PKG_CONFIG_INCLUDEDIR "\${prefix}/${CMAKE_INSTALL_INCLUDEDIR}")
endif()
if(IS_ABSOLUTE ${CMAKE_INSTALL_LIBDIR})
  set(PKG_CONFIG_LIBDIR ${CMAKE_INSTALL_LIBDIR})
else()
  set(PKG_CONFIG_LIBDIR "\${exec_prefix}/${CMAKE_INSTALL_LIBDIR}")
endif()
configure_file(
  ${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}.pc.in
  ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc 
  @ONLY )
install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# CMake config files
set(CONFIG_TARGETS_FILE "improc_infrastructure_config_targets.cmake")
set(EXPORT_DESTINATION_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME}_targets FILE ${CONFIG_TARGETS_FILE} DESTINATION ${EXPORT_DESTINATION_DIR})

include(CMakePackageConfigHelpers)
configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/cmake/improc_infrastructure_config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/improc_infrastructure_config.cmake 
  INSTALL_DESTINATION ${EXPORT_DESTINATION_DIR} )
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/improc_infrastructure_config_version.cmake
  VERSION ${IMPROC_SUPERPROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/improc_infrastructure_config.cmake 
              ${CMAKE_CURRENT_BINARY_DIR}/improc_infrastructure_config_version.cmake
        DESTINATION ${EXPORT_DESTINATION_DIR})
