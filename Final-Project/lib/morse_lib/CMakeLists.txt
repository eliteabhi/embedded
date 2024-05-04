# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Name your project
project(morse_blink_led)

# Specify src directory
set(SRC_DIR ./src)

# Source files here
set(SRCS ${SRC_DIR}/blink.c ${SRC_DIR}/delay.c ${SRC_DIR}/morse.c)

# For release builds
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release build")

    add_executable(morse_blink_led ${MAIN} ${SRCS})
    target_compile_definitions(morse_blink_led PRIVATE RELEASE)
    target_compile_options(morse_blink_led PRIVATE -O3)

    target_compile_definitions(test_leds PRIVATE RELEASE)
    target_compile_options(test_leds PRIVATE -O3)
endif()

# For debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug build")

    add_executable(morse_blink_led ${MAIN} ${SRCS})
    target_compile_definitions(morse_blink_led PRIVATE RELEASE)
    target_compile_options(morse_blink_led PRIVATE -g DEBUG)

    target_compile_definitions(test_leds PRIVATE RELEASE)
    target_compile_options(test_leds PRIVATE -g DEBUG)
endif()
