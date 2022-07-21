cmake_minimum_required(VERSION 3.22)
project(Optimization_project)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

add_executable(Optimization_project main.cpp Optimization.h Optimization.cpp)