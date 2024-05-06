cmake_minimum_required(VERSION 3.10)

project(BMP280 VERSION 1.0)

add_library(bmp280 STATIC bmp280_i2c.c)
