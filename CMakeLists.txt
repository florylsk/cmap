cmake_minimum_required(VERSION 3.21)
project(cmap)
set(CMAKE_C_FLAGS "-Wall -Wextra -O3 -fopenmp")
add_executable(cmap main.c)
