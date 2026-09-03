cmake_minimum_required(VERSION 4.3)
project(hyprcompat C)

set(CMAKE_C_STANDARD 11)

add_executable(hyprcompat
        src/main.c
        src/lexer.c
        src/lexer.h)
