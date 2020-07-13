# TODO: Better looking doc page - https://devblogs.microsoft.com/cppblog/clear-functional-c-documentation-with-sphinx-breathe-doxygen-cmake/
find_package(Doxygen REQUIRED)

MESSAGE(STATUS "===============================================================" )
MESSAGE(STATUS "===================== NEON ENGINE - Docs ======================" )
MESSAGE(STATUS "===============================================================" )

# This will be the main output of our command
set(DOXYGEN_INPUT_DIR ${PROJECT_SOURCE_DIR}/NeonEngine)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

# Replace variables inside @@ with the current values
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR}) # Doxygen won't create this for us
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${HEADER_FILES}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_OUT}
                   MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                   COMMENT "Generating docs")

add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})

MESSAGE(STATUS "DOXYGEN_INPUT_DIR: " ${DOXYGEN_INPUT_DIR})
MESSAGE(STATUS "DOXYGEN_OUTPUT_DIR: " ${DOXYGEN_OUTPUT_DIR})
MESSAGE(STATUS "DOXYGEN_INDEX_FILE: " ${DOXYGEN_INDEX_FILE})
MESSAGE(STATUS "DOXYFILE_IN: " ${DOXYFILE_IN})
MESSAGE(STATUS "DOXYFILE_OUT: " ${DOXYFILE_OUT})
