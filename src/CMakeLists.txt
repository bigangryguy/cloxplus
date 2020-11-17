cmake_minimum_required(VERSION 3.17)
project(clox)

find_package(fmt REQUIRED)

set(SOURCE_CODE
        main.cpp
        common.h
        value.h value.cpp
        opcode.h
        chunk.cpp chunk.h
        debugger.cpp debugger.h
        vm.cpp vm.h
        interpretresult.h
        repl.cpp repl.h
        compiler.cpp compiler.h)

add_executable(clox ${SOURCE_CODE})

target_link_libraries(clox fmt::fmt)