#
# Include/Lib Variables
#
LOCAL_INC = /usr/local/include
LOCAL_LIB = /usr/local/lib
SRC = ./NeonEngine/src
SRC_CPP := $(shell find $(SRC) ! -path */tests/* ! -path */debugging/* ! -name "main.cpp" -name "*.cpp")
# Testing
# TEST_H := $(wildcard $(SRC)/tests/*.cpp)
# TEST_FILENAME := object_test.cpp
# TEST_SRC := $(SRC)/tests/$(TEST_FILENAME)
# Debugging
DEBUG_H := $(SRC)/utils/debugging/debug.h
DEBUG_SRC := $(wildcard $(SRC)/utils/debugging/*.cpp)
OBJ_FILES := $(patsubst %.cpp, %.o, $(notdir $(SRC_CPP:.cpp=.o)))

#
# Dependencies Directories
#
GLFW := ./Dependencies/glfw
GLFW_INC := $(GLFW)/include
GLFW_LIB := $(GLFW)/lib-mingw

GLAD := ./Dependencies/glad
GLAD_INC := $(GLAD)/include

GLM := ./Dependencies/glm

TINYOBJLOADER := ./Dependencies/tinyobjloader-1.0.6

STB_IMAGE := ./Dependencies/stb_image

#
# Build Variables
#
CC = g++
CC_FLAGS = -Wall

GL_OPTIONS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lglfw3
LDLIBS = -L/opt/X11/lib $(GL_OPTIONS) -L$(LOCAL_LIB) -L$(GLFW_LIB)

INCS = -I/opt/X11/include -I$(LOCAL_INC) -I$(GLFW_INC) -I$(GLAD_INC) -I$(GLM) -I$(TINYOBJLOADER) -I$(STB_IMAGE)

OPTIONS= $(CC_FLAGS) $(INCS)

# The first item in the file is what will be made if you just type
# make (i.e. with no arguments).
# main: $(SRC)/main.cpp glad.o $(OBJ_FILES)
# 	$(CC) $(SRC)/main.cpp glad.o $(OBJ_FILES) $(OPTIONS) $(LDLIBS) -o $@ $^
# obj/%.o: $(SRC)/%.cpp
# 	$(CC) $(OPTIONS) -c -o $@ $<
all: main

main: $(SRC)/main.cpp glad.o $(OBJ_FILES)
	$(CC) $(SRC)/main.cpp glad.o $(OBJ_FILES) $(OPTIONS) $(LDLIBS) -o main

#
# Utils
#
debug.o: $(DEBUG_H)
	$(CC) $(DEBUG_SRC) -c $(OPTIONS)

fileUtils.o: $(SRC)/utils/file_utils/fileUtils.h $(SRC)/utils/file_utils/fileUtils.cpp
	$(CC) $(SRC)/utils/file_utils/fileUtils.cpp -c $(OPTIONS)

objloader.o: $(SRC)/utils/obj_loader/objloader.h $(SRC)/utils/obj_loader/objloader.cpp $(TINYOBJLOADER)/tiny_obj_loader.h
	$(CC) $(SRC)/utils/obj_loader/objloader.cpp -c $(OPTIONS)

#
# App
#
window.o: $(SRC)/app/window.h $(SRC)/app/window.cpp glad.o
	$(CC) $(SRC)/app/window.cpp -c $(OPTIONS)

#
# Shaders
#
texture.o: $(SRC)/shaders/texture.h $(SRC)/shaders/texture.cpp glad.o
	$(CC) $(SRC)/shaders/texture.cpp -c $(OPTIONS)
program.o: $(SRC)/shaders/program.h $(SRC)/shaders/program.cpp glad.o
	$(CC) $(SRC)/shaders/program.cpp -c $(OPTIONS)
shader.o: $(SRC)/shaders/shader.h $(SRC)/shaders/shader.cpp glad.o
	$(CC) $(SRC)/shaders/shader.cpp -c $(OPTIONS)
#
# Graphics
#
model.o: $(SRC)/graphics/entities/model.h $(SRC)/graphics/entities/model.cpp glad.o mesh.o
	$(CC) $(SRC)/graphics/entities/model.cpp -c $(OPTIONS)

mesh.o: $(SRC)/graphics/entities/mesh.h $(SRC)/graphics/entities/mesh.cpp
	$(CC) $(SRC)/graphics/entities/mesh.cpp -c $(OPTIONS)

camera.o: $(SRC)/graphics/cameras/camera.h $(SRC)/graphics/cameras/camera.cpp glad.o
	$(CC) $(SRC)/graphics/cameras/camera.cpp -c $(OPTIONS)

indexBuffer.o: $(SRC)/graphics/buffers/indexBuffer.h $(SRC)/graphics/buffers/indexBuffer.cpp glad.o
	$(CC) $(SRC)/graphics/buffers/indexBuffer.cpp -c $(OPTIONS)

vertexArray.o: $(SRC)/graphics/buffers/vertexArray.h $(SRC)/graphics/buffers/vertexArray.cpp glad.o
	$(CC) $(SRC)/graphics/buffers/vertexArray.cpp -c $(OPTIONS)

vertexBuffer.o: $(SRC)/graphics/buffers/vertexBuffer.h $(SRC)/graphics/buffers/vertexBuffer.cpp glad.o
	$(CC) $(SRC)/graphics/buffers/vertexBuffer.cpp -c $(OPTIONS)
#
# GLAD
#
glad.o: $(GLAD_INC)/glad/glad.h $(SRC)/glad/glad.c
	$(CC) $(SRC)/glad/glad.c -c $(OPTIONS)

# pattern to clean the directory
clean: 
	rm -f main *.o
	
.PHONY: all clean

print-%  : ; @echo $* = $($*)