cmake_minimum_required(VERSION 3.13)
project(Merkle_Trees)

set(CMAKE_CXX_STANDARD 17)

add_executable(Merkle_Trees main.cpp md5.h md5.cpp block.h block.cpp chain.h chain.cpp)