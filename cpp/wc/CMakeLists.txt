cmake_minimum_required(VERSION 3.29)
project(wc)

set(CMAKE_CXX_STANDARD 17)

add_executable(wc src/main.cpp
        src/wc.h)
