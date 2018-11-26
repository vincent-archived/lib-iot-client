cmake_minimum_required(VERSION 3.5.1)

project(lib-iot-client)

set(CMAKE_C_STANDARD 90)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_VERBOSE_MAKEFILE FALSE)

add_subdirectory(serialport)

enable_testing()

add_subdirectory(test)
