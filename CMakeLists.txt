cmake_minimum_required(VERSION 3.28)
project(BDZ_Matrix)

set(CMAKE_CXX_STANDARD 20)

add_executable(BDZ_Matrix main.cpp
        matrix.h
        rational.cpp
)
