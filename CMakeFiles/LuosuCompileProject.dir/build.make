# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/luosu/codeproject/LuosuCompile

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luosu/codeproject/LuosuCompile

# Include any dependencies generated for this target.
include CMakeFiles/LuosuCompileProject.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/LuosuCompileProject.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/LuosuCompileProject.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LuosuCompileProject.dir/flags.make

CMakeFiles/LuosuCompileProject.dir/compiler.c.o: CMakeFiles/LuosuCompileProject.dir/flags.make
CMakeFiles/LuosuCompileProject.dir/compiler.c.o: compiler.c
CMakeFiles/LuosuCompileProject.dir/compiler.c.o: CMakeFiles/LuosuCompileProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luosu/codeproject/LuosuCompile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/LuosuCompileProject.dir/compiler.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LuosuCompileProject.dir/compiler.c.o -MF CMakeFiles/LuosuCompileProject.dir/compiler.c.o.d -o CMakeFiles/LuosuCompileProject.dir/compiler.c.o -c /home/luosu/codeproject/LuosuCompile/compiler.c

CMakeFiles/LuosuCompileProject.dir/compiler.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LuosuCompileProject.dir/compiler.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luosu/codeproject/LuosuCompile/compiler.c > CMakeFiles/LuosuCompileProject.dir/compiler.c.i

CMakeFiles/LuosuCompileProject.dir/compiler.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LuosuCompileProject.dir/compiler.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luosu/codeproject/LuosuCompile/compiler.c -o CMakeFiles/LuosuCompileProject.dir/compiler.c.s

CMakeFiles/LuosuCompileProject.dir/cprocess.c.o: CMakeFiles/LuosuCompileProject.dir/flags.make
CMakeFiles/LuosuCompileProject.dir/cprocess.c.o: cprocess.c
CMakeFiles/LuosuCompileProject.dir/cprocess.c.o: CMakeFiles/LuosuCompileProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luosu/codeproject/LuosuCompile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/LuosuCompileProject.dir/cprocess.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LuosuCompileProject.dir/cprocess.c.o -MF CMakeFiles/LuosuCompileProject.dir/cprocess.c.o.d -o CMakeFiles/LuosuCompileProject.dir/cprocess.c.o -c /home/luosu/codeproject/LuosuCompile/cprocess.c

CMakeFiles/LuosuCompileProject.dir/cprocess.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LuosuCompileProject.dir/cprocess.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luosu/codeproject/LuosuCompile/cprocess.c > CMakeFiles/LuosuCompileProject.dir/cprocess.c.i

CMakeFiles/LuosuCompileProject.dir/cprocess.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LuosuCompileProject.dir/cprocess.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luosu/codeproject/LuosuCompile/cprocess.c -o CMakeFiles/LuosuCompileProject.dir/cprocess.c.s

CMakeFiles/LuosuCompileProject.dir/lex_process.c.o: CMakeFiles/LuosuCompileProject.dir/flags.make
CMakeFiles/LuosuCompileProject.dir/lex_process.c.o: lex_process.c
CMakeFiles/LuosuCompileProject.dir/lex_process.c.o: CMakeFiles/LuosuCompileProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luosu/codeproject/LuosuCompile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/LuosuCompileProject.dir/lex_process.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LuosuCompileProject.dir/lex_process.c.o -MF CMakeFiles/LuosuCompileProject.dir/lex_process.c.o.d -o CMakeFiles/LuosuCompileProject.dir/lex_process.c.o -c /home/luosu/codeproject/LuosuCompile/lex_process.c

CMakeFiles/LuosuCompileProject.dir/lex_process.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LuosuCompileProject.dir/lex_process.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luosu/codeproject/LuosuCompile/lex_process.c > CMakeFiles/LuosuCompileProject.dir/lex_process.c.i

CMakeFiles/LuosuCompileProject.dir/lex_process.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LuosuCompileProject.dir/lex_process.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luosu/codeproject/LuosuCompile/lex_process.c -o CMakeFiles/LuosuCompileProject.dir/lex_process.c.s

CMakeFiles/LuosuCompileProject.dir/lexer.c.o: CMakeFiles/LuosuCompileProject.dir/flags.make
CMakeFiles/LuosuCompileProject.dir/lexer.c.o: lexer.c
CMakeFiles/LuosuCompileProject.dir/lexer.c.o: CMakeFiles/LuosuCompileProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luosu/codeproject/LuosuCompile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/LuosuCompileProject.dir/lexer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LuosuCompileProject.dir/lexer.c.o -MF CMakeFiles/LuosuCompileProject.dir/lexer.c.o.d -o CMakeFiles/LuosuCompileProject.dir/lexer.c.o -c /home/luosu/codeproject/LuosuCompile/lexer.c

CMakeFiles/LuosuCompileProject.dir/lexer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LuosuCompileProject.dir/lexer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luosu/codeproject/LuosuCompile/lexer.c > CMakeFiles/LuosuCompileProject.dir/lexer.c.i

CMakeFiles/LuosuCompileProject.dir/lexer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LuosuCompileProject.dir/lexer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luosu/codeproject/LuosuCompile/lexer.c -o CMakeFiles/LuosuCompileProject.dir/lexer.c.s

CMakeFiles/LuosuCompileProject.dir/main.c.o: CMakeFiles/LuosuCompileProject.dir/flags.make
CMakeFiles/LuosuCompileProject.dir/main.c.o: main.c
CMakeFiles/LuosuCompileProject.dir/main.c.o: CMakeFiles/LuosuCompileProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luosu/codeproject/LuosuCompile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/LuosuCompileProject.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LuosuCompileProject.dir/main.c.o -MF CMakeFiles/LuosuCompileProject.dir/main.c.o.d -o CMakeFiles/LuosuCompileProject.dir/main.c.o -c /home/luosu/codeproject/LuosuCompile/main.c

CMakeFiles/LuosuCompileProject.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LuosuCompileProject.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luosu/codeproject/LuosuCompile/main.c > CMakeFiles/LuosuCompileProject.dir/main.c.i

CMakeFiles/LuosuCompileProject.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LuosuCompileProject.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luosu/codeproject/LuosuCompile/main.c -o CMakeFiles/LuosuCompileProject.dir/main.c.s

CMakeFiles/LuosuCompileProject.dir/token.c.o: CMakeFiles/LuosuCompileProject.dir/flags.make
CMakeFiles/LuosuCompileProject.dir/token.c.o: token.c
CMakeFiles/LuosuCompileProject.dir/token.c.o: CMakeFiles/LuosuCompileProject.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/luosu/codeproject/LuosuCompile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/LuosuCompileProject.dir/token.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/LuosuCompileProject.dir/token.c.o -MF CMakeFiles/LuosuCompileProject.dir/token.c.o.d -o CMakeFiles/LuosuCompileProject.dir/token.c.o -c /home/luosu/codeproject/LuosuCompile/token.c

CMakeFiles/LuosuCompileProject.dir/token.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/LuosuCompileProject.dir/token.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/luosu/codeproject/LuosuCompile/token.c > CMakeFiles/LuosuCompileProject.dir/token.c.i

CMakeFiles/LuosuCompileProject.dir/token.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/LuosuCompileProject.dir/token.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/luosu/codeproject/LuosuCompile/token.c -o CMakeFiles/LuosuCompileProject.dir/token.c.s

# Object files for target LuosuCompileProject
LuosuCompileProject_OBJECTS = \
"CMakeFiles/LuosuCompileProject.dir/compiler.c.o" \
"CMakeFiles/LuosuCompileProject.dir/cprocess.c.o" \
"CMakeFiles/LuosuCompileProject.dir/lex_process.c.o" \
"CMakeFiles/LuosuCompileProject.dir/lexer.c.o" \
"CMakeFiles/LuosuCompileProject.dir/main.c.o" \
"CMakeFiles/LuosuCompileProject.dir/token.c.o"

# External object files for target LuosuCompileProject
LuosuCompileProject_EXTERNAL_OBJECTS =

LuosuCompileProject: CMakeFiles/LuosuCompileProject.dir/compiler.c.o
LuosuCompileProject: CMakeFiles/LuosuCompileProject.dir/cprocess.c.o
LuosuCompileProject: CMakeFiles/LuosuCompileProject.dir/lex_process.c.o
LuosuCompileProject: CMakeFiles/LuosuCompileProject.dir/lexer.c.o
LuosuCompileProject: CMakeFiles/LuosuCompileProject.dir/main.c.o
LuosuCompileProject: CMakeFiles/LuosuCompileProject.dir/token.c.o
LuosuCompileProject: CMakeFiles/LuosuCompileProject.dir/build.make
LuosuCompileProject: helpers/libHelpers.a
LuosuCompileProject: CMakeFiles/LuosuCompileProject.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/luosu/codeproject/LuosuCompile/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking C executable LuosuCompileProject"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LuosuCompileProject.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LuosuCompileProject.dir/build: LuosuCompileProject
.PHONY : CMakeFiles/LuosuCompileProject.dir/build

CMakeFiles/LuosuCompileProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LuosuCompileProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LuosuCompileProject.dir/clean

CMakeFiles/LuosuCompileProject.dir/depend:
	cd /home/luosu/codeproject/LuosuCompile && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luosu/codeproject/LuosuCompile /home/luosu/codeproject/LuosuCompile /home/luosu/codeproject/LuosuCompile /home/luosu/codeproject/LuosuCompile /home/luosu/codeproject/LuosuCompile/CMakeFiles/LuosuCompileProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LuosuCompileProject.dir/depend

