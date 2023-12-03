cmake_minimum_required(VERSION 3.16.3)

project(aoc_utils
        LANGUAGES CXX
        VERSION 1.0)

include(../cmake/compiler_options.cmake)

add_library(utils STATIC string_list.cpp string_utils.cpp)
add_executable(test test.cpp)
target_link_libraries(test PRIVATE utils)

