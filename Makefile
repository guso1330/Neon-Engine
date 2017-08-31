LOCAL_INC = /usr/local/include
LOCAL_LIB = /usr/local/lib
SRC = ./NeonEngine/src

GLFW = ./Dependencies/glfw
GLFW_INC = $(GLFW)/include
GLFW_LIB = $(GLFW)/lib-mingw

GLAD = ./Dependencies/glad
GLAD_INC = $(GLAD)/include

GLM = ./Dependencies/glm

CC = g++

CC_OPTIONS = -Wall

GL_OPTIONS = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo -lglfw3
LDLIBS = -L/opt/X11/lib $(GL_OPTIONS) -L$(LOCAL_LIB) -L$(GLFW_LIB)

INCS = -I/opt/X11/include -I$(LOCAL_INC) -I$(GLFW_INC) -I$(GLAD_INC) -I$(GLM)

OPTIONS= $(CC_OPTIONS) $(INCS)

# The first item in the file is what will be made if you just type
# make (i.e. with no arguments).
all: main
	
main: $(SRC)/main.cpp glad.o window.o shader.o fileUtils.o
	$(CC) $(SRC)/main.cpp glad.o window.o shader.o fileUtils.o $(OPTIONS) $(LDLIBS) -o main

fileUtils.o: $(SRC)/utils/fileUtils.h $(SRC)/utils/fileUtils.cpp
	$(CC) $(SRC)/utils/fileUtils.cpp -c $(OPTIONS)

shader.o: $(SRC)/shaders/shader.h $(SRC)/shaders/shader.cpp glad.o
	$(CC) $(SRC)/shaders/shader.cpp -c $(OPTIONS)

window.o: $(SRC)/app/window.h $(SRC)/app/window.cpp glad.o
	$(CC) $(SRC)/app/window.cpp -c $(OPTIONS)

glad.o: $(GLAD_INC)/glad/glad.h $(SRC)/glad/glad.cpp
	$(CC) $(SRC)/glad/glad.cpp -c $(OPTIONS)

# pattern to clean the directory
clean: 
	rm -f main *.o

# CC = gcc
# CXX = g++

# INCLUDES = -I$(glfw_inc) -I$(glad_inc)
# LIBRARIES = -L$(glfw_lib) 

# glfw = d:/external/glfw-3.1
# glfw_inc = $(glfw)/include
# glfw_lib = $(glfw)/lib64

# glad = d:/external/glad-c
# glad_inc = $(glad)/include

# CFLAGS = -Wall -ggdb -O3 $(INCLUDES)
# CXXFLAGS = -Wall -ggdb -O3 $(INCLUDES)
# LDFLAGS = $(LIBRARIES) -lglfw3 -lopengl32 -lglu32 -lgdi32

# TARGET = main.exe
# cpp_files = main.cpp
# objects = $(cpp_files:.cpp=.o) glad.o
# headers =

# all: $(TARGET)

# $(TARGET): $(objects) 
#         $(CXX) -o $@ $^ $(LDFLAGS)

# .PHONY : clean
# clean :
#         -rm $(TARGET) $(objects)