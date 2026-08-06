cmake_minimum_required(VERSION 4.1)
project(Socket_library C)

set(CMAKE_C_STANDARD 23)

add_library(Socket_library SHARED library.c)
target_include_directories(Socket_library PUBLIC .)
