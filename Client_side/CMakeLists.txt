cmake_minimum_required(VERSION 4.1)
project(Client_side C)

set(CMAKE_C_STANDARD 23)

add_executable(Client_side main.c)

include_directories("/home/highlow/CLionProjects/Socket_library")
target_link_libraries(Client_side "/home/highlow/CLionProjects/Socket_library/cmake-build-debug/libSocket_library.so")