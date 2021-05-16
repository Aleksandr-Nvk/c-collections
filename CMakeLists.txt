cmake_minimum_required(VERSION 3.19)
project(C_collections C)

set(CMAKE_C_STANDARD 99)

add_executable(Main main.c libcollections_source/collections_generic.h)
include_directories(include libcollections_source)

find_library(Collections collections lib)
target_link_libraries(Main LINK_PUBLIC ${Collections})