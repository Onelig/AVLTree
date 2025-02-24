cmake_minimum_required(VERSION 3.10)

project(AVLTreeProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(AVLTree src/main.cpp)
include_directories(include)