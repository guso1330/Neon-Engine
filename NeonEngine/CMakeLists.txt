# TODO:
#	- Move split out this CMakeLists file to both ./NeonEngine and ./NeonEngine-test

# Project definition
cmake_minimum_required(VERSION 3.9.1)
project(NeonEngine_lib VERSION 0.0.1 DESCRIPTION "NeonEngine library")

# Source files
set(LIB_DIR "${PROJECT_SOURCE_DIR}/Dependencies")
set(SRC_DIR "${PROJECT_SOURCE_DIR}/NeonEngine")
set(TEST_DIR "${PROJECT_SOURCE_DIR}/NeonEngine-test")
file(GLOB_RECURSE SRC_FILES "${SRC_DIR}/**.cpp")
file(GLOB_RECURSE TEMPLATE_FILES "${SRC_DIR}/**.tpp")
file(GLOB_RECURSE HEADER_FILES "${SRC_DIR}/**.h*")
file(GLOB_RECURSE TEST_FILES "${TEST_DIR}/**-test.cpp")

# library
add_library(${PROJECT_NAME} STATIC ${SRC_FILES}) # TODO: Add header files to add_library?

# Executable definition and properties
target_include_directories(${PROJECT_NAME} PUBLIC "${SRC_DIR}")
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
add_library("glad" STATIC "${GLAD_DIR}/src/glad.c")
target_include_directories("glad" PRIVATE "${GLAD_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${GLAD_DIR}/include")
target_link_libraries(${PROJECT_NAME} "glad")

# spdlog
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

# EventSystem
set(EVENTSYSTEM_DIR "${LIB_DIR}/EventSystem")
set(EVENT_SYSTEM_BUILD_MAIN OFF CACHE INTERNAL "Build the EventSystem main")
add_subdirectory(${EVENTSYSTEM_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC "${EVENTSYSTEM_DIR}/include")
target_link_libraries(${PROJECT_NAME} "EventSystemLib")

# imgui
set(IMGUI_DIR "${LIB_DIR}/imgui")
file(GLOB IMGUI_FILES 
	"${IMGUI_DIR}/*.cpp"
	"${IMGUI_DIR}/examples/imgui_impl_opengl3.cpp"
	"${IMGUI_DIR}/examples/imgui_impl_glfw.cpp"
)
add_library("imgui" STATIC "${IMGUI_FILES}")
target_include_directories("imgui" PRIVATE 
	"${IMGUI_DIR}"
	"${GLFW_DIR}/include"
	"${GLAD_DIR}/include"
)
target_include_directories(${PROJECT_NAME} PUBLIC "${IMGUI_DIR}")
target_link_libraries(${PROJECT_NAME} "imgui")

# tests
set(CMAKE_MACOSX_RPATH 1)
set(TEST_BINARY "NeonEngine-test")
add_executable(${TEST_BINARY} ${TEST_FILES})
add_test(NAME ${TEST_BINARY} COMMAND ${TEST_BINARY})
set_property(TARGET ${TEST_BINARY} PROPERTY CXX_STANDARD 11)
target_link_libraries(${TEST_BINARY} gtest ${PROJECT_NAME})

# google test
set(GOOGLETEST_DIR "${LIB_DIR}/googletest")
add_subdirectory(${GOOGLETEST_DIR})

# Printing
MESSAGE(STATUS "===============================================================" )
MESSAGE(STATUS "========================NEON ENGINE============================" )
MESSAGE(STATUS "===============================================================" )
MESSAGE(STATUS "						                                        " )
MESSAGE(STATUS "                     Variable Paths                            " )
MESSAGE(STATUS "						                                        " )
MESSAGE(STATUS "LIB_DIR: " ${LIB_DIR})
MESSAGE(STATUS "ASSIMP_DIR: " ${ASSIMP_DIR})
MESSAGE(STATUS "IMGUI_DIR: " ${IMGUI_DIR})
MESSAGE(STATUS "GLFW_DIR: " ${GLFW_DIR})
MESSAGE(STATUS "GLAD_DIR: " ${GLAD_DIR})
MESSAGE(STATUS "SPDLOG_DIR: " ${SPDLOG_DIR})
MESSAGE(STATUS "EVENTSYSTEM_DIR: " ${EVENTSYSTEM_DIR})
MESSAGE(STATUS "GOOGLETEST_DIR: " ${GOOGLETEST_DIR})
MESSAGE(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
MESSAGE(STATUS "SRC_DIR:" ${SRC_DIR})
MESSAGE(STATUS "TEST_DIR: ${TEST_DIR}")
foreach(src_file ${SRC_FILES})
	MESSAGE(STATUS "SOURCE FILE: " ${src_file})
endforeach(src_file)
foreach(template_file ${TEMPLATE_FILES})
	MESSAGE(STATUS "TEMPLATE FILE: " ${template_file})
endforeach(template_file)
foreach(header_file ${HEADER_FILES})
	MESSAGE(STATUS "HEADER FILE: " ${header_file})
endforeach(header_file)
foreach(test_file ${TEST_FILES})
	MESSAGE(STATUS "TEST FILE: " ${test_file})
endforeach(test_file)
