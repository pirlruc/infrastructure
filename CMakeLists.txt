cmake_minimum_required(VERSION 3.14-3.18)

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

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
  set(CMAKE_DEBUG_POSTFIX d)
  option(BUILD_SHARED_LIBS           "Build using shared libraries" ON)
  option(IMPROC_WITH_TESTS 			     "Building library with tests"  ON)
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

# BOOST
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost
  GIT_TAG        boost-1.77.0
  SOURCE_DIR      ${PROJECT_SOURCE_DIR}/external/boost
)
FetchContent_MakeAvailable(boost)

message(STATUS "Build ${PROJECT_NAME} Version: ${PROJECT_VERSION}")
message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")
message(STATUS "Install Dir: ${CMAKE_INSTALL_PREFIX}")

add_library(
  ${PROJECT_NAME}
  
  ${PROJECT_SOURCE_DIR}/include

  ${PROJECT_SOURCE_DIR}/src/folder.cpp
  ${PROJECT_SOURCE_DIR}/src/file.cpp
  ${PROJECT_SOURCE_DIR}/src/string.cpp
  ${PROJECT_SOURCE_DIR}/src/application_context.cpp
)
add_library(improc::infrastructure ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD           17)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD_REQUIRED  TRUE)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE        CXX)
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION                ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX          ${CMAKE_DEBUG_POSTFIX})

target_include_directories  (${PROJECT_NAME}   PRIVATE   ${PROJECT_SOURCE_DIR}/include)
target_include_directories  (${PROJECT_NAME}   INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                                               $<INSTALL_INTERFACE:include> )

# Link dependencies
target_link_libraries       (${PROJECT_NAME}   PRIVATE   spdlog)
target_link_libraries       (${PROJECT_NAME}   PRIVATE   jsoncpp_lib)
target_link_libraries       (${PROJECT_NAME}   PRIVATE   boost_algorithm)
target_link_libraries       (${PROJECT_NAME}   INTERFACE spdlog)
target_link_libraries       (${PROJECT_NAME}   INTERFACE jsoncpp_lib)
target_link_libraries       (${PROJECT_NAME}   INTERFACE boost_algorithm)

# Tests configuration
if(IMPROC_WITH_TESTS)
  add_subdirectory(${PROJECT_SOURCE_DIR}/test     ${CMAKE_BINARY_DIR}/infrastructure_test)
endif()

if(PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  add_subdirectory(${PROJECT_SOURCE_DIR}/version  ${CMAKE_BINARY_DIR}/version)
endif()

# Install configuration
set(${PROJECT_NAME}_libs ${PROJECT_NAME} spdlog jsoncpp_lib boost_algorithm)
install(
  TARGETS     ${${PROJECT_NAME}_libs}
  DESTINATION lib
  EXPORT      ${PROJECT_NAME}_target 
)
install(FILES   ${PROJECT_SOURCE_DIR}/external/jsoncpp/LICENSE                                        DESTINATION share/licenses/improc/jsoncpp)
install(FILES   ${PROJECT_SOURCE_DIR}/external/spdlog/LICENSE                                         DESTINATION share/licenses/improc/spdlog)
install(FILES   ${PROJECT_SOURCE_DIR}/external/boost/LICENSE_1_0.txt                                  DESTINATION share/licenses/improc/boost)

install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/benchmark/benchmark_singleton.hpp DESTINATION include/improc/infrastructure/benchmark)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/benchmark/benchmark_singleton.tpp DESTINATION include/improc/infrastructure/benchmark)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/context/application_context.hpp   DESTINATION include/improc/infrastructure/context)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/context/environment_context.hpp   DESTINATION include/improc/infrastructure/context)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/context/environment_context.tpp   DESTINATION include/improc/infrastructure/context)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/filesystem/file.hpp               DESTINATION include/improc/infrastructure/filesystem)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/filesystem/folder_policies.hpp    DESTINATION include/improc/infrastructure/filesystem)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/filesystem/folder_policies.tpp    DESTINATION include/improc/infrastructure/filesystem)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/filesystem/folder.hpp             DESTINATION include/improc/infrastructure/filesystem)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logging/logger_infrastructure.hpp DESTINATION include/improc/infrastructure/logging)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logging/logger_singleton.hpp      DESTINATION include/improc/infrastructure/logging)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/logging/logger_singleton.tpp      DESTINATION include/improc/infrastructure/logging)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/math/math.hpp                     DESTINATION include/improc/infrastructure/math)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/math/math.tpp                     DESTINATION include/improc/infrastructure/math)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/parsers/json_parser.hpp           DESTINATION include/improc/infrastructure/parsers)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/parsers/json_parser.tpp           DESTINATION include/improc/infrastructure/parsers)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/infrastructure/string.hpp                        DESTINATION include/improc/infrastructure)
install(FILES   ${PROJECT_SOURCE_DIR}/include/improc/exception.hpp                                    DESTINATION include/improc)
