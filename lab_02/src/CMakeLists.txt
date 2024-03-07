cmake_minimum_required(VERSION 3.26)
project(src)

set(CMAKE_CXX_STANDARD 17)

add_executable(src main.cpp
        mtr.cpp
        measure.cpp
        alg.cpp)
