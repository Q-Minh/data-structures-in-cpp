﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("data-structures-and-algorithms-cpp")

# prevent visual studio warning saying CMAKE_TOOLCHAIN_FILE is not used
message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}.")

# Include sub-projects.
add_subdirectory ("data-structures-and-algorithms-cpp")
add_subdirectory("tests")