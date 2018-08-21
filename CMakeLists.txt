# cmake_minimum_required(VERSION <specify CMake version here>)
project(HashTable C)

set(CMAKE_C_STANDARD 99)

add_executable(HashTable hashtable.c hashtable.h hashfunctions.c hashfunctions.h)