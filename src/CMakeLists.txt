cmake_minimum_required(VERSION 3.17)
project(clox)

find_package(fmt REQUIRED)

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