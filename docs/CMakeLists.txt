cmake_minimum_required(VERSION 3.14-3.18)

find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT  ${PROJECT_SOURCE_DIR}/docs/doxyfile.in)
set(DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/docs/doxyfile.out)

configure_file(${DOXYGEN_INPUT} ${DOXYGEN_OUTPUT} @ONLY)
message("-- Doxygen configured")

add_custom_target(
  docs
  COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUTPUT}
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Generating documentation..."
  VERBATIM
)
