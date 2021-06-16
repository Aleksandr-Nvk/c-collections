cmake_minimum_required(VERSION 3.19)
project(C_collections C)

set(CMAKE_C_STANDARD 99)

add_executable(Main main.c usages/list_usage.c usages/linked_list_usage.c usages/stack_usage.c usages/queue_usage.c
        usages/dictionary_usage.c source/list.c source/linked_list.c source/stack.c source/queue.c source/dictionary.c
        )

include_directories(source include)