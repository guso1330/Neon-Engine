#
# Include/Lib Variables
#
LOCAL_INC = /usr/local/include
LOCAL_LIB = /usr/local/lib
SRC = ./NeonEngine/src
SRC_CPP := $(shell find $(SRC) ! -path */tests/* ! -name "main.cpp" -name "*.cpp")
TEST_H := $(wildcard $(SRC)/tests/*.h)
OBJ_FILES := $(patsubst %.cpp, %.o, $(notdir $(SRC_CPP:.cpp=.o)))

#
# Dependencies Directories
#
GLFW = ./Dependencies/glfw
GLFW_INC = $(GLFW)/include
GLFW_LIB = $(GLFW)/lib-mingw

GLAD = ./Dependencies/glad
GLAD_INC = $(GLAD)/include

GLM = ./Dependencies/glm

#
# Build Variables
#
CC = g++
CC_FLAGS = -Wall

GL_OPTIONS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lglfw3
LDLIBS = -L/opt/X11/lib $(GL_OPTIONS) -L$(LOCAL_LIB) -L$(GLFW_LIB)

INCS = -I/opt/X11/include -I$(LOCAL_INC) -I$(GLFW_INC) -I$(GLAD_INC) -I$(GLM)

OPTIONS= $(CC_FLAGS) $(INCS)

# The first item in the file is what will be made if you just type
# make (i.e. with no arguments).
all: main

# main: $(SRC)/main.cpp glad.o $(OBJ_FILES)
# 	$(CC) $(SRC)/main.cpp glad.o $(OBJ_FILES) $(OPTIONS) $(LDLIBS) -o $@ $^

# obj/%.o: $(SRC)/%.cpp
# 	$(CC) $(OPTIONS) -c -o $@ $<
	
main: $(SRC)/main.cpp test.o glad.o $(OBJ_FILES)
	$(CC) $(SRC)/main.cpp glad.o $(OBJ_FILES) $(OPTIONS) $(LDLIBS) -o main

test.o: $(TEST_H)
	$(CC) $(TEST_H) -c $(OPTIONS)

fileUtils.o: $(SRC)/utils/file_utils/fileUtils.h $(SRC)/utils/file_utils/fileUtils.cpp
	$(CC) $(SRC)/utils/file_utils/fileUtils.cpp -c $(OPTIONS)

shader.o: $(SRC)/shaders/shader.h $(SRC)/shaders/shader.cpp glad.o
	$(CC) $(SRC)/shaders/shader.cpp -c $(OPTIONS)

window.o: $(SRC)/app/window.h $(SRC)/app/window.cpp glad.o
	$(CC) $(SRC)/app/window.cpp -c $(OPTIONS)

indexBuffer.o: $(SRC)/graphics/buffers/indexBuffer.h $(SRC)/graphics/buffers/indexBuffer.cpp glad.o
	$(CC) $(SRC)/graphics/buffers/indexBuffer.cpp -c $(OPTIONS)

vertexArray.o: $(SRC)/graphics/buffers/vertexArray.h $(SRC)/graphics/buffers/vertexArray.cpp glad.o
	$(CC) $(SRC)/graphics/buffers/vertexArray.cpp -c $(OPTIONS)

vertexBuffer.o: $(SRC)/graphics/buffers/vertexBuffer.h $(SRC)/graphics/buffers/vertexBuffer.cpp glad.o
	$(CC) $(SRC)/graphics/buffers/vertexBuffer.cpp -c $(OPTIONS)

glad.o: $(GLAD_INC)/glad/glad.h $(SRC)/glad/glad.c
	$(CC) $(SRC)/glad/glad.c -c $(OPTIONS)

# pattern to clean the directory
clean: 
	rm -f main *.o
	
.PHONY: all clean

print-%  : ; @echo $* = $($*)