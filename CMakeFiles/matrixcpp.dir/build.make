# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/912/bin/cmake

# The command to remove a file.
RM = /snap/cmake/912/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices

# Include any dependencies generated for this target.
include CMakeFiles/matrixcpp.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/matrixcpp.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/matrixcpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matrixcpp.dir/flags.make

CMakeFiles/matrixcpp.dir/src/Matrix.cpp.o: CMakeFiles/matrixcpp.dir/flags.make
CMakeFiles/matrixcpp.dir/src/Matrix.cpp.o: src/Matrix.cpp
CMakeFiles/matrixcpp.dir/src/Matrix.cpp.o: CMakeFiles/matrixcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/matrixcpp.dir/src/Matrix.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/matrixcpp.dir/src/Matrix.cpp.o -MF CMakeFiles/matrixcpp.dir/src/Matrix.cpp.o.d -o CMakeFiles/matrixcpp.dir/src/Matrix.cpp.o -c /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/Matrix.cpp

CMakeFiles/matrixcpp.dir/src/Matrix.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matrixcpp.dir/src/Matrix.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/Matrix.cpp > CMakeFiles/matrixcpp.dir/src/Matrix.cpp.i

CMakeFiles/matrixcpp.dir/src/Matrix.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matrixcpp.dir/src/Matrix.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/Matrix.cpp -o CMakeFiles/matrixcpp.dir/src/Matrix.cpp.s

CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.o: CMakeFiles/matrixcpp.dir/flags.make
CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.o: src/SharedCalculator.cpp
CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.o: CMakeFiles/matrixcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.o -MF CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.o.d -o CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.o -c /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/SharedCalculator.cpp

CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/SharedCalculator.cpp > CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.i

CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/SharedCalculator.cpp -o CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.s

CMakeFiles/matrixcpp.dir/src/Serializer.cpp.o: CMakeFiles/matrixcpp.dir/flags.make
CMakeFiles/matrixcpp.dir/src/Serializer.cpp.o: src/Serializer.cpp
CMakeFiles/matrixcpp.dir/src/Serializer.cpp.o: CMakeFiles/matrixcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/matrixcpp.dir/src/Serializer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/matrixcpp.dir/src/Serializer.cpp.o -MF CMakeFiles/matrixcpp.dir/src/Serializer.cpp.o.d -o CMakeFiles/matrixcpp.dir/src/Serializer.cpp.o -c /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/Serializer.cpp

CMakeFiles/matrixcpp.dir/src/Serializer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matrixcpp.dir/src/Serializer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/Serializer.cpp > CMakeFiles/matrixcpp.dir/src/Serializer.cpp.i

CMakeFiles/matrixcpp.dir/src/Serializer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matrixcpp.dir/src/Serializer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/Serializer.cpp -o CMakeFiles/matrixcpp.dir/src/Serializer.cpp.s

CMakeFiles/matrixcpp.dir/src/main.cpp.o: CMakeFiles/matrixcpp.dir/flags.make
CMakeFiles/matrixcpp.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/matrixcpp.dir/src/main.cpp.o: CMakeFiles/matrixcpp.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/matrixcpp.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/matrixcpp.dir/src/main.cpp.o -MF CMakeFiles/matrixcpp.dir/src/main.cpp.o.d -o CMakeFiles/matrixcpp.dir/src/main.cpp.o -c /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/main.cpp

CMakeFiles/matrixcpp.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matrixcpp.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/main.cpp > CMakeFiles/matrixcpp.dir/src/main.cpp.i

CMakeFiles/matrixcpp.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matrixcpp.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/src/main.cpp -o CMakeFiles/matrixcpp.dir/src/main.cpp.s

# Object files for target matrixcpp
matrixcpp_OBJECTS = \
"CMakeFiles/matrixcpp.dir/src/Matrix.cpp.o" \
"CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.o" \
"CMakeFiles/matrixcpp.dir/src/Serializer.cpp.o" \
"CMakeFiles/matrixcpp.dir/src/main.cpp.o"

# External object files for target matrixcpp
matrixcpp_EXTERNAL_OBJECTS =

matrixcpp: CMakeFiles/matrixcpp.dir/src/Matrix.cpp.o
matrixcpp: CMakeFiles/matrixcpp.dir/src/SharedCalculator.cpp.o
matrixcpp: CMakeFiles/matrixcpp.dir/src/Serializer.cpp.o
matrixcpp: CMakeFiles/matrixcpp.dir/src/main.cpp.o
matrixcpp: CMakeFiles/matrixcpp.dir/build.make
matrixcpp: CMakeFiles/matrixcpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable matrixcpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matrixcpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/matrixcpp.dir/build: matrixcpp
.PHONY : CMakeFiles/matrixcpp.dir/build

CMakeFiles/matrixcpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matrixcpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matrixcpp.dir/clean

CMakeFiles/matrixcpp.dir/depend:
	cd /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices /home/yanis/Desktop/Projets/thread-vs-fork-in-cpp---Matrices/CMakeFiles/matrixcpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matrixcpp.dir/depend

