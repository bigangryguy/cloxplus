cmake_minimum_required(VERSION 3.17)
project(testclox)

find_package(fmt REQUIRED)
find_package(Catch2 REQUIRED)

set(SOURCE_CODE
        ../src/common.h
        ../src/value.h
        ../src/opcode.h
        ../src/chunk.h ../src/chunk.cpp
        ../src/debugger.h ../src/debugger.cpp
        main.cpp
        TestDebugger.cpp)

add_executable(testclox ${SOURCE_CODE})

target_link_libraries(testclox fmt::fmt Catch2::Catch2)