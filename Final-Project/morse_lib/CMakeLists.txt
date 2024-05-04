# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Name your project
project(morse_blink_led)

# Source files here
set(SRCS ./blink.c ./delay.c ./morse.c)

target_link_libraries(morse_lib ${SRCS})
target_compile_options(morse_lib PRIVATE -O3)

