cmake_minimum_required(VERSION 3.19)
project(C_collections C)

set(CMAKE_C_STANDARD 99)

add_executable(Main main.c collections_source/collections_generic.h examples/list_usage.c examples/linked_list_usage.c
               examples/stack_usage.c examples/queue_usage.c examples/dictionary_usage.c examples_declarations.h
               collections_source/list.c collections_source/linked_list.c collections_source/stack.c
               collections_source/queue.c collections_source/dictionary.c)
include_directories(collections_source include)