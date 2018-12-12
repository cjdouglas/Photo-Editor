cmake_minimum_required(VERSION 3.11)
project(photoeditor)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(HALIDE_DISTRIB_DIR "/home/cdoug/ext/halide")
include("${HALIDE_DISTRIB_DIR}/halide.cmake")

halide_library(format_chunky SRCS src/generators/format_chunky.cc)

set(GCC_COVERAGE_LINK_FLAGS "-lglfw -lGL -lGLEW -lHalide -ljpeg -lpng16 -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

include_directories(src)
set(SOURCES src/editor/main.cc)

add_executable(main ${SOURCES})
target_link_libraries(main PUBLIC format_chunky)
