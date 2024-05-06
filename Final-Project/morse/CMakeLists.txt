# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Name your project
project(morse_blink_led)

# Source files here
set(SRCS ./blink.c ./delay.c ./morse.c)

add_library(morse ${SRCS})

# target_link_libraries(morse_bin ${SRCS})
# target_compile_options(morse_bin PRIVATE -O3)

