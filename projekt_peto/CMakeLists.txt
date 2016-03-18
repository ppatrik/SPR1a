cmake_minimum_required(VERSION 3.3)
project(userman)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")

set(SOURCE_FILES userman.c basic.c person.c)
add_executable(userman ${SOURCE_FILES})