cmake_minimum_required(VERSION 3.17)
project(clox)

set(CMAKE_CXX_STANDARD 20)

find_package(fmt)

set(SOURCE_CODE
        main.cpp
        common.h
        value.h
        opcode.h
        chunk.h chunk.cpp
        debugger.h debugger.cpp
)

add_executable(clox ${SOURCE_CODE})

target_link_libraries(clox fmt::fmt)