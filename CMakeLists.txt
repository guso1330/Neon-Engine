# Project definition
cmake_minimum_required(VERSION 3.9.1)
project(main)

# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/NeonEngine/src")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies")
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)

include_directories(
	${LIB_DIR}/glm
	${LIB_DIR}/stb_image
	${LIB_DIR}/tinyobjloader-1.0.6
	${LIB_DIR}/assimp-4.1.0/include
	${LIB_DIR}/json-3.1.2/include
)

# Executable definition and properties
add_executable(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# assimp
set(ASSIMP_DIR "${LIB_DIR}/assimp-4.1.0")
add_subdirectory("${ASSIMP_DIR}")
target_link_libraries(${PROJECT_NAME} "assimp" ${ASSIMP_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE "${ASSIMP_DIR}/include")

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# Printing
MESSAGE( STATUS "===============================================================" )
MESSAGE( STATUS "========================NEON ENGINE============================" )
MESSAGE( STATUS "===============================================================" )
# MESSAGE( STATUS "						                                        " )
# MESSAGE( STATUS "                       Source Paths                            " )
# MESSAGE( STATUS "						                                        " )
# MESSAGE( STATUS "CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR} )
# MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )
# MESSAGE( STATUS "CMAKE_SOURCE_DIR: " ${CMAKE_SOURCE_DIR} )
# MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )
# MESSAGE( STATUS "						                                        " )
# MESSAGE( STATUS "                       Build Paths                            " )
# MESSAGE( STATUS "						                                        " )
# MESSAGE( STATUS "CMAKE_RUNTIME_OUTPUT_DIRECTORY: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
# MESSAGE( STATUS "CMAKE_ARCHIVE_OUTPUT_DIRECTORY: " ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
# MESSAGE( STATUS "CMAKE_LIBRARY_OUTPUT_DIRECTORY: " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
MESSAGE( STATUS "						                                        " )
MESSAGE( STATUS "                     Variable Paths                            " )
MESSAGE( STATUS "						                                        " )
MESSAGE( STATUS "SRC_DIR: " ${SRC_DIR} )
MESSAGE( STATUS "LIB_DIR: " ${LIB_DIR} )
MESSAGE( STATUS "GLFW_DIR: " ${GLFW_DIR} )
foreach(file ${SRC_FILES})
	MESSAGE( STATUS "SOURCE FILE: " ${file} )
endforeach(file)
# foreach(file ${SRC_FILES})
# 	MESSAGE( STATUS "HEADER FILE: " ${file} )
# endforeach(file)
MESSAGE( STATUS "						                                        " )
MESSAGE( STATUS "===============================================================" )
MESSAGE( STATUS "===============================================================" )
MESSAGE( STATUS "===============================================================" )