cmake_minimum_required(VERSION 3.13)
project(myfillit)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

add_executable(myfillit
        includes/fillit.h
        srcs/board.c
        srcs/fillit.c
        srcs/lib.c
        srcs/listfunc.c
        srcs/main.c
        srcs/reading.c
        srcs/slavastrdup.c
        srcs/solving.c
        srcs/validation.c
		srcs/sample)
