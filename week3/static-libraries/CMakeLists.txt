set(SRC_DIR ./)

# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name and version
project(ArithmeticLibraries VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable for the main program
add_executable(lib_math ${SRC_DIR}/main.c)

subdirs(lib_int_arithmetic lib_float_arithmetic)

# Link the example program with the static library
target_link_libraries(lib_math intarithmetic floatarithmetic)