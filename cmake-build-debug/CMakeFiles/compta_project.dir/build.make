# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.2.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.2.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\agath\Documents\GitHub\compta_project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\agath\Documents\GitHub\compta_project\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/compta_project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/compta_project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/compta_project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/compta_project.dir/flags.make

CMakeFiles/compta_project.dir/main.c.obj: CMakeFiles/compta_project.dir/flags.make
CMakeFiles/compta_project.dir/main.c.obj: C:/Users/agath/Documents/GitHub/compta_project/main.c
CMakeFiles/compta_project.dir/main.c.obj: CMakeFiles/compta_project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\agath\Documents\GitHub\compta_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/compta_project.dir/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/compta_project.dir/main.c.obj -MF CMakeFiles\compta_project.dir\main.c.obj.d -o CMakeFiles\compta_project.dir\main.c.obj -c C:\Users\agath\Documents\GitHub\compta_project\main.c

CMakeFiles/compta_project.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/compta_project.dir/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\agath\Documents\GitHub\compta_project\main.c > CMakeFiles\compta_project.dir\main.c.i

CMakeFiles/compta_project.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/compta_project.dir/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.1\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\agath\Documents\GitHub\compta_project\main.c -o CMakeFiles\compta_project.dir\main.c.s

# Object files for target compta_project
compta_project_OBJECTS = \
"CMakeFiles/compta_project.dir/main.c.obj"

# External object files for target compta_project
compta_project_EXTERNAL_OBJECTS =

compta_project.exe: CMakeFiles/compta_project.dir/main.c.obj
compta_project.exe: CMakeFiles/compta_project.dir/build.make
compta_project.exe: CMakeFiles/compta_project.dir/linkLibs.rsp
compta_project.exe: CMakeFiles/compta_project.dir/objects1.rsp
compta_project.exe: CMakeFiles/compta_project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\agath\Documents\GitHub\compta_project\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable compta_project.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\compta_project.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/compta_project.dir/build: compta_project.exe
.PHONY : CMakeFiles/compta_project.dir/build

CMakeFiles/compta_project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\compta_project.dir\cmake_clean.cmake
.PHONY : CMakeFiles/compta_project.dir/clean

CMakeFiles/compta_project.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\agath\Documents\GitHub\compta_project C:\Users\agath\Documents\GitHub\compta_project C:\Users\agath\Documents\GitHub\compta_project\cmake-build-debug C:\Users\agath\Documents\GitHub\compta_project\cmake-build-debug C:\Users\agath\Documents\GitHub\compta_project\cmake-build-debug\CMakeFiles\compta_project.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/compta_project.dir/depend

