cmake_minimum_required(VERSION 3.23)
project(Bomberman C)

set(CMAKE_C_STANDARD 99)

set(PROJECT_HEADERS
        main.h
        )
set(PROJECT_SOURCES
        main.c
        )

add_executable(untitled1 ${PROJECT_SOURCES} ${PROJECT_HEADERS})

add_executable(Bomberman ${PROJECT_SOURCES} ${PROJECT_HEADERS} main.h)
