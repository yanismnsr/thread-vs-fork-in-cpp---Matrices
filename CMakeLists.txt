# cmake_minimum_required(VERSION <specify CMake version here>)
cmake_minimum_required(VERSION 3.16)
project(matrixcpp)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_BUILD_TYPE Release)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include_directories(include)
include_directories(include/matrixcpp)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(matrixcpp
        include/matrixcpp/Matrix.h
        include/matrixcpp/SharedCalculator.h
        include/matrixcpp/Serializer.h
        src/Matrix.cpp
        src/SharedCalculator.cpp
        src/Serializer.cpp
        src/main.cpp)
        
target_link_libraries(matrixcpp Threads::Threads)