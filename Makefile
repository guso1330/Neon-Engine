# Include Variables
LOCAL_INC = /usr/local/include
LOCAL_LIB = /usr/local/lib
SRC = ./NeonEngine/src

# Dependencies Directories
GLFW = ./Dependencies/glfw
GLFW_INC = $(GLFW)/include
GLFW_LIB = $(GLFW)/lib-mingw

GLAD = ./Dependencies/glad
GLAD_INC = $(GLAD)/include

GLM = ./Dependencies/glm

# Build Variables
CC = g++
CC_FLAGS = -Wall

GL_OPTIONS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lglfw3
LDLIBS = -L/opt/X11/lib $(GL_OPTIONS) -L$(LOCAL_LIB) -L$(GLFW_LIB)

INCS = -I/opt/X11/include -I$(LOCAL_INC) -I$(GLFW_INC) -I$(GLAD_INC) -I$(GLM)

OPTIONS= $(CC_FLAGS) $(INCS)

# The first item in the file is what will be made if you just type
# make (i.e. with no arguments).
all: main
	
main: $(SRC)/main.cpp glad.o window.o shader.o fileUtils.o
	$(CC) $(SRC)/main.cpp glad.o window.o shader.o fileUtils.o $(OPTIONS) $(LDLIBS) -o main

fileUtils.o: $(SRC)/utils/file_utils/fileUtils.h $(SRC)/utils/file_utils/fileUtils.cpp
	$(CC) $(SRC)/utils/file_utils/fileUtils.cpp -c $(OPTIONS)

shader.o: $(SRC)/shaders/shader.h $(SRC)/shaders/shader.cpp glad.o
	$(CC) $(SRC)/shaders/shader.cpp -c $(OPTIONS)

window.o: $(SRC)/app/window.h $(SRC)/app/window.cpp glad.o
	$(CC) $(SRC)/app/window.cpp -c $(OPTIONS)

glad.o: $(GLAD_INC)/glad/glad.h $(SRC)/glad/glad.c
	$(CC) $(SRC)/glad/glad.c -c $(OPTIONS)

# pattern to clean the directory
clean: 
	rm -f main *.o
	
.PHONY: all clean