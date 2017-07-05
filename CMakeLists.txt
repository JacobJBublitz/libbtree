cmake_minimum_required(VERSION 3.8)
project(libbtree)

set(CMAKE_C_STANDARD 99)

add_library(libbtree SHARED src/btree.c src/btree.h)
set_target_properties(libbtree PROPERTIES PREFIX "")
target_include_directories(libbtree PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(tests)