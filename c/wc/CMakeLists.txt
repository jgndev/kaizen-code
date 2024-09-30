cmake_minimum_required(VERSION 3.29)
project(c C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(wc
        src/wc.c
        src/wc.h)
