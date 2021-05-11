cmake_minimum_required(VERSION 3.19)
project(C_collections C)

set(CMAKE_C_STANDARD 99)

add_executable(Main main.c linked_list.h stack.h queue.h)
