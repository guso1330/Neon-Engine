# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/guso133/Documents/Neon-Engine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/guso133/Documents/Neon-Engine

# Include any dependencies generated for this target.
include CMakeFiles/glad.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glad.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glad.dir/flags.make

CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o: CMakeFiles/glad.dir/flags.make
CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o: Dependencies/glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/guso133/Documents/Neon-Engine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o   -c /Users/guso133/Documents/Neon-Engine/Dependencies/glad/src/glad.c

CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/guso133/Documents/Neon-Engine/Dependencies/glad/src/glad.c > CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.i

CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/guso133/Documents/Neon-Engine/Dependencies/glad/src/glad.c -o CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.s

CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o.requires:

.PHONY : CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o.requires

CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o.provides: CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o.requires
	$(MAKE) -f CMakeFiles/glad.dir/build.make CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o.provides.build
.PHONY : CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o.provides

CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o.provides.build: CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o


# Object files for target glad
glad_OBJECTS = \
"CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o"

# External object files for target glad
glad_EXTERNAL_OBJECTS =

libglad.a: CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o
libglad.a: CMakeFiles/glad.dir/build.make
libglad.a: CMakeFiles/glad.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/guso133/Documents/Neon-Engine/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglad.a"
	$(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glad.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glad.dir/build: libglad.a

.PHONY : CMakeFiles/glad.dir/build

CMakeFiles/glad.dir/requires: CMakeFiles/glad.dir/Dependencies/glad/src/glad.c.o.requires

.PHONY : CMakeFiles/glad.dir/requires

CMakeFiles/glad.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glad.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glad.dir/clean

CMakeFiles/glad.dir/depend:
	cd /Users/guso133/Documents/Neon-Engine && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/guso133/Documents/Neon-Engine /Users/guso133/Documents/Neon-Engine /Users/guso133/Documents/Neon-Engine /Users/guso133/Documents/Neon-Engine /Users/guso133/Documents/Neon-Engine/CMakeFiles/glad.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glad.dir/depend

