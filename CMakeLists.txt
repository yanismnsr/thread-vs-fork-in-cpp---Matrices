# cmake_minimum_required(VERSION <specify CMake version here>)
project(matrixcpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)
include_directories(include/matrixcpp)

find_package (Threads)

add_executable(matrixcpp
        include/matrixcpp/Matrix.h
        src/Matrix.cpp
        src/main.cpp)
        
target_link_libraries (matrixcpp ${CMAKE_THREAD_LIBS_INIT})