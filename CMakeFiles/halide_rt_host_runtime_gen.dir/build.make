# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cdoug/gitroot/photoeditor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cdoug/gitroot/photoeditor

# Utility rule file for halide_rt_host_runtime_gen.

# Include the progress variables for this target.
include CMakeFiles/halide_rt_host_runtime_gen.dir/progress.make

CMakeFiles/halide_rt_host_runtime_gen: genfiles/halide_rt_host/halide_rt_host.a


genfiles/halide_rt_host/halide_rt_host.a: halide_library_runtime.generator_binary
	./halide_library_runtime.generator_binary -o /home/cdoug/gitroot/photoeditor/./genfiles/halide_rt_host -r halide_rt_host target=host

halide_rt_host_runtime_gen: CMakeFiles/halide_rt_host_runtime_gen
halide_rt_host_runtime_gen: genfiles/halide_rt_host/halide_rt_host.a
halide_rt_host_runtime_gen: CMakeFiles/halide_rt_host_runtime_gen.dir/build.make

.PHONY : halide_rt_host_runtime_gen

# Rule to build all files generated by this target.
CMakeFiles/halide_rt_host_runtime_gen.dir/build: halide_rt_host_runtime_gen

.PHONY : CMakeFiles/halide_rt_host_runtime_gen.dir/build

CMakeFiles/halide_rt_host_runtime_gen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/halide_rt_host_runtime_gen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/halide_rt_host_runtime_gen.dir/clean

CMakeFiles/halide_rt_host_runtime_gen.dir/depend:
	cd /home/cdoug/gitroot/photoeditor && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cdoug/gitroot/photoeditor /home/cdoug/gitroot/photoeditor /home/cdoug/gitroot/photoeditor /home/cdoug/gitroot/photoeditor /home/cdoug/gitroot/photoeditor/CMakeFiles/halide_rt_host_runtime_gen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/halide_rt_host_runtime_gen.dir/depend

