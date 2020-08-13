cmake_minimum_required(VERSION 3.17)
project(clox)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_CODE
        main.cpp
        common.h
        opcode.h
        chunk.h chunk.cpp
        debugger.h debugger.cpp)

add_executable(clox ${SOURCE_CODE})