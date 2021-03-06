cmake_minimum_required(VERSION 3.11)
project(photoeditor)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HALIDE_DISTRIB_DIR "/home/cdoug/ext/halide")
include("${HALIDE_DISTRIB_DIR}/halide.cmake")

halide_library(format_chunky SRCS src/generators/format_chunky.cc)

set(GCC_COVERAGE_LINK_FLAGS "-lglfw -lGL -lGLEW -lHalide -ljpeg -lpng16 -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

include_directories(src)
set(SOURCES 
	src/editor/main.cc 
	src/rendering/renderer.cc 
	src/gui/app.cc
	src/util/image.cc)

# Disable building extras we won't need (pure C++ project)
set(NANOGUI_BUILD_EXAMPLE OFF CACHE BOOL " " FORCE)
set(NANOGUI_BUILD_PYTHON  OFF CACHE BOOL " " FORCE)
set(NANOGUI_INSTALL       OFF CACHE BOOL " " FORCE)
set(EIGEN3_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext/nanogui/ext/eigen)
set(NANOGUI_EIGEN_INCLUDE_DIR ${EIGEN3_INCLUDE_DIR} CACHE BOOL " " FORCE)

# Add the configurations from nanogui
add_subdirectory(ext/nanogui)

# For reliability of parallel build, make the NanoGUI targets dependencies
set_property(TARGET glfw glfw_objects nanogui PROPERTY FOLDER "dependencies")

# Various preprocessor definitions have been generated by NanoGUI
add_definitions(${NANOGUI_EXTRA_DEFS})

# On top of adding the path to nanogui/include, you may need extras
include_directories(${NANOGUI_EXTRA_INCS} ${EIGEN3_INCLUDE_DIR})

add_executable(main ${SOURCES})
target_link_libraries(main PUBLIC format_chunky nanogui ${NANOGUI_EXTRA_LIBS})
