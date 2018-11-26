cmake_minimum_required(VERSION 3.5.1)

project(iot-client-serialport C)

set(src
        src/serialport.c
        src/serialport.h)

add_library(iot-client-serialport ${arch} ${src})