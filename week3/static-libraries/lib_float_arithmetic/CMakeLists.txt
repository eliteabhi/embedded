set(SRC_DIR ./src)
set(LIB_DIR ./lib)

# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name and version
project(FloatArithmeticLibrary VERSION 1.0)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add an executable for the main program
add_executable(float_math ${SRC_DIR}/main.c)

file(GLOB CPP_FILES ${LIB_DIR}/*.cpp )

# Add library source files
add_library(floatarithmetic STATIC ${CPP_FILES})

# Link the example program with the static library
target_link_libraries(float_math floatarithmetic)