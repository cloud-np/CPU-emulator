cmake_minimum_required(VERSION 3.20)
project(ask_6_organwsh C)

set(CMAKE_C_STANDARD 11)

add_executable(ask_6_organwsh main.c parse_mips.h helpers.h mips.c)
