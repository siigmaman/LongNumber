# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/arsen/cppprojects/sasa/LongNumber

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug

# Include any dependencies generated for this target.
include src/CMakeFiles/LongNumber.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/LongNumber.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/LongNumber.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/LongNumber.dir/flags.make

src/CMakeFiles/LongNumber.dir/LongNumber.cpp.o: src/CMakeFiles/LongNumber.dir/flags.make
src/CMakeFiles/LongNumber.dir/LongNumber.cpp.o: /home/arsen/cppprojects/sasa/LongNumber/src/LongNumber.cpp
src/CMakeFiles/LongNumber.dir/LongNumber.cpp.o: src/CMakeFiles/LongNumber.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/LongNumber.dir/LongNumber.cpp.o"
	cd /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/LongNumber.dir/LongNumber.cpp.o -MF CMakeFiles/LongNumber.dir/LongNumber.cpp.o.d -o CMakeFiles/LongNumber.dir/LongNumber.cpp.o -c /home/arsen/cppprojects/sasa/LongNumber/src/LongNumber.cpp

src/CMakeFiles/LongNumber.dir/LongNumber.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/LongNumber.dir/LongNumber.cpp.i"
	cd /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arsen/cppprojects/sasa/LongNumber/src/LongNumber.cpp > CMakeFiles/LongNumber.dir/LongNumber.cpp.i

src/CMakeFiles/LongNumber.dir/LongNumber.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/LongNumber.dir/LongNumber.cpp.s"
	cd /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arsen/cppprojects/sasa/LongNumber/src/LongNumber.cpp -o CMakeFiles/LongNumber.dir/LongNumber.cpp.s

src/CMakeFiles/LongNumber.dir/Helpers.cpp.o: src/CMakeFiles/LongNumber.dir/flags.make
src/CMakeFiles/LongNumber.dir/Helpers.cpp.o: /home/arsen/cppprojects/sasa/LongNumber/src/Helpers.cpp
src/CMakeFiles/LongNumber.dir/Helpers.cpp.o: src/CMakeFiles/LongNumber.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/LongNumber.dir/Helpers.cpp.o"
	cd /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/LongNumber.dir/Helpers.cpp.o -MF CMakeFiles/LongNumber.dir/Helpers.cpp.o.d -o CMakeFiles/LongNumber.dir/Helpers.cpp.o -c /home/arsen/cppprojects/sasa/LongNumber/src/Helpers.cpp

src/CMakeFiles/LongNumber.dir/Helpers.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/LongNumber.dir/Helpers.cpp.i"
	cd /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/arsen/cppprojects/sasa/LongNumber/src/Helpers.cpp > CMakeFiles/LongNumber.dir/Helpers.cpp.i

src/CMakeFiles/LongNumber.dir/Helpers.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/LongNumber.dir/Helpers.cpp.s"
	cd /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/arsen/cppprojects/sasa/LongNumber/src/Helpers.cpp -o CMakeFiles/LongNumber.dir/Helpers.cpp.s

# Object files for target LongNumber
LongNumber_OBJECTS = \
"CMakeFiles/LongNumber.dir/LongNumber.cpp.o" \
"CMakeFiles/LongNumber.dir/Helpers.cpp.o"

# External object files for target LongNumber
LongNumber_EXTERNAL_OBJECTS =

src/libLongNumber.a: src/CMakeFiles/LongNumber.dir/LongNumber.cpp.o
src/libLongNumber.a: src/CMakeFiles/LongNumber.dir/Helpers.cpp.o
src/libLongNumber.a: src/CMakeFiles/LongNumber.dir/build.make
src/libLongNumber.a: src/CMakeFiles/LongNumber.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libLongNumber.a"
	cd /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/LongNumber.dir/cmake_clean_target.cmake
	cd /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LongNumber.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/LongNumber.dir/build: src/libLongNumber.a
.PHONY : src/CMakeFiles/LongNumber.dir/build

src/CMakeFiles/LongNumber.dir/clean:
	cd /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src && $(CMAKE_COMMAND) -P CMakeFiles/LongNumber.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/LongNumber.dir/clean

src/CMakeFiles/LongNumber.dir/depend:
	cd /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/arsen/cppprojects/sasa/LongNumber /home/arsen/cppprojects/sasa/LongNumber/src /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src /home/arsen/cppprojects/sasa/LongNumber/cmake-build-debug/src/CMakeFiles/LongNumber.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/CMakeFiles/LongNumber.dir/depend

