cmake_minimum_required(VERSION 3.25)
project(Clion C)

set(CMAKE_C_STANDARD 99)

add_executable(Clion main.c display.h display.c game.h game.c dictionary.h dictionary.c
        database.h
        database.c)
