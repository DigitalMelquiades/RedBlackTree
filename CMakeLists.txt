cmake_minimum_required(VERSION 4.1)
project(RedBlackTree)

set(CMAKE_CXX_STANDARD 20)

add_executable(RedBlackTree main.cpp
        Node.h
        RedBlackTree.h
        RedBlackTree.cpp)
