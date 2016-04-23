cmake_minimum_required(VERSION 3.5)
project(PatrikShell)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu99 -Wformat-security")

set(SOURCE_FILES patrikshell.c config.c config.h history.c history.h runner.c runner.h errors.h)
add_executable(PatrikShell ${SOURCE_FILES})