set(SRC_DIR ./src)
set(LIB_DIR ./lib)

# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name and version
project(IntArithmeticLibrary VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add an executable for the main program
add_executable(integer_math ${SRC_DIR}/main.c)

file(GLOB C_FILES ${LIB_DIR}/*.c )

# Add library source files
add_library(intarithmetic STATIC ${C_FILES})

# Link the example program with the static library
target_link_libraries(integer_math intarithmetic)