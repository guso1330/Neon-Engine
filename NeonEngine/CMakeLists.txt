# Project definition
cmake_minimum_required(VERSION 3.9.1)
project(NeonEngine_lib VERSION 0.0.1 DESCRIPTION "NeonEngine library")

# Source files
set(LIB_DIR "${PROJECT_SOURCE_DIR}/dependencies")
file(GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/NeonEngine/*.cpp")

add_library(${PROJECT_NAME} ${SRC_FILES})

# Executable definition and properties
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)

# assimp
set(ASSIMP_DIR "${LIB_DIR}/assimp")
add_subdirectory(${ASSIMP_DIR})
target_link_libraries(${PROJECT_NAME} "assimp" ${ASSIMP_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC "${ASSIMP_DIR}/include")

# GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
add_subdirectory(${GLFW_DIR})
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")
target_include_directories(${PROJECT_NAME} PUBLIC "${GLFW_DIR}/include")
target_compile_definitions(${PROJECT_NAME} PRIVATE "GLFW_INCLUDE_NONE")

# glad
set(GLAD_DIR "${LIB_DIR}/glad")
add_library("glad" "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad" "${CMAKE_DL_LIBS}")

# glad
set(SPDLOG_DIR "${LIB_DIR}/spdlog")
set(SPDLOG_BUILD_EXAMPLE OFF CACHE INTERNAL "Build the spdlog example programs")
set(SPDLOG_BUILD_TESTS OFF CACHE INTERNAL "Build the spdlog test programs")
set(SPDLOG_BUILD_BENCH OFF CACHE INTERNAL "Build the spdlog bench programs")
add_subdirectory(${SPDLOG_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC "${SPDLOG_DIR}/include")
target_link_libraries(${PROJECT_NAME} "spdlog" ${DSPDLOG_COMPILED_LIB})

# glm && stb_image
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_DIR}/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${LIB_DIR}/stb_image)

# Printing
MESSAGE( STATUS "===============================================================" )
MESSAGE( STATUS "========================NEON ENGINE============================" )
MESSAGE( STATUS "===============================================================" )
MESSAGE( STATUS "						                                        " )
MESSAGE( STATUS "                     Variable Paths                            " )
MESSAGE( STATUS "						                                        " )
MESSAGE( STATUS "LIB_DIR: "    ${LIB_DIR} )
MESSAGE( STATUS "ASSIMP_DIR: " ${ASSIMP_DIR} )
MESSAGE( STATUS "GLFW_DIR: "   ${GLFW_DIR} )
MESSAGE( STATUS "GLAD_DIR: "   ${GLAD_DIR} )
MESSAGE( STATUS "SPDLOG_DIR: "   ${SPDLOG_DIR} )
MESSAGE( STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}" )
foreach(file ${SRC_FILES})
	MESSAGE( STATUS "SOURCE FILE: " ${file} )
endforeach(file)
