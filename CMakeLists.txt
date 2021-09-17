cmake_minimum_required(VERSION 3.14-3.18)

if(NOT DEFINED IMPROC_SUPERPROJECT_VERSION)
  set(IMPROC_SUPERPROJECT_VERSION 1.0.0)
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
  option(BUILD_SHARED_LIBS           "Build using shared libraries" ON)
  set(CMAKE_DEBUG_POSTFIX d)
endif()

# Add external dependencies
# SPDLOG
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY  https://github.com/gabime/spdlog
  GIT_TAG         v1.9.2
  SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/spdlog
)
FetchContent_MakeAvailable(spdlog)
target_include_directories(spdlog INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/spdlog/include>
                                            $<INSTALL_INTERFACE:include> )

# JSONCPP
FetchContent_Declare(
  jsoncpp
  GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp
  GIT_TAG        1.9.4
  SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/jsoncpp
)
set(JSONCPP_WITH_TESTS    OFF)
set(JSONCPP_WITH_EXAMPLE  OFF)
FetchContent_MakeAvailable(jsoncpp)
# Already added in jsoncpp CMakeLists
# target_include_directories(jsoncpp_lib INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/jsoncpp/include>
#                                                                    $<INSTALL_INTERFACE:include> )

message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

add_library(
  ${PROJECT_NAME}
  
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/src/file.cpp
)
add_library(improc::infrastructure ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD           17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE        CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION                ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})

target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/src)
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                               $<INSTALL_INTERFACE:include> )
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
                                               $<INSTALL_INTERFACE:include> )

# Link dependencies
target_link_libraries       (${PROJECT_NAME}   PRIVATE   spdlog)
target_link_libraries       (${PROJECT_NAME}   PRIVATE   jsoncpp_lib)
target_link_libraries       (${PROJECT_NAME}   INTERFACE spdlog)
target_link_libraries       (${PROJECT_NAME}   INTERFACE jsoncpp_lib)

# Tests configuration
if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test     ${CMAKE_BINARY_DIR}/test)
  add_subdirectory(${PROJECT_SOURCE_DIR}/version  ${CMAKE_BINARY_DIR}/version)
endif()

# Install configuration
set(${PROJECT_NAME}_libs ${PROJECT_NAME} spdlog jsoncpp_lib)
install(
  TARGETS     ${${PROJECT_NAME}_libs}
  DESTINATION lib
  EXPORT      ${PROJECT_NAME}_target 
)
install(FILES   ${PROJECT_SOURCE_DIR}/external/jsoncpp/LICENSE                                  DESTINATION share/licenses/improc/jsoncpp)
install(FILES   ${PROJECT_SOURCE_DIR}/external/spdlog/LICENSE                                   DESTINATION share/licenses/improc/spdlog)

install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/file.hpp                    DESTINATION include/improc/infrastructure)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logger_singleton.hpp        DESTINATION include/improc/infrastructure)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/benchmark_singleton.hpp     DESTINATION include/improc/infrastructure)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logger_infrastructure.hpp   DESTINATION include/improc/infrastructure)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/jsonfile_parser.hpp         DESTINATION include/improc/infrastructure)
