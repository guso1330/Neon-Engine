# Project definition
cmake_minimum_required(VERSION 3.9.1)
project(SandBox VERSION 0.0.1 DESCRIPTION "NeonEngine SandBox Application")

# Source files
file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SRC_FILES})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
target_link_libraries(${PROJECT_NAME} NeonEngine_lib)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/NeonEngine")

set(RES_DIR "${PROJECT_SOURCE_DIR}/res")
set(RES_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/res")
add_custom_command(
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${RES_DIR} ${RES_DEST_DIR}
	DEPENDS ${RES_DEST_DIR}
	COMMENT "Symbolic link for res folder from ${RES_DIR} => ${RES_DEST_DIR}"
)

# Printing
MESSAGE( STATUS "===============================================================" )
MESSAGE( STATUS "========================NeonEngine SandBox=====================" )
MESSAGE( STATUS "===============================================================" )
MESSAGE( STATUS "						                                        " )
MESSAGE( STATUS "                     Variable Paths                            " )
MESSAGE( STATUS "						                                        " )
MESSAGE( STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}" )
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}" )
foreach(file ${SRC_FILES})
	MESSAGE( STATUS "SOURCE FILE: " ${file} )
endforeach(file)
MESSAGE( STATUS "						                                        " )
MESSAGE( STATUS "===============================================================" )
MESSAGE( STATUS "===============================================================" )
MESSAGE( STATUS "===============================================================" )
