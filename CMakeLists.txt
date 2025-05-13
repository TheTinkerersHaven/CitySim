cmake_minimum_required(VERSION 3.14.0)
project(CitySim)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -Wpedantic)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(CitySim ${SOURCES})

