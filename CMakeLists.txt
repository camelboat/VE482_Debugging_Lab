cmake_minimum_required(VERSION 3.8)
project(lab7_correct)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c dlist.c)
add_executable(lab7_correct ${SOURCE_FILES})