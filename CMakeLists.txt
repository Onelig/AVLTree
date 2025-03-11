cmake_minimum_required(VERSION 3.10)

project(AVLTreeProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Connect Google Test
add_subdirectory(external/googletest)

enable_testing()

# Create tests
add_executable(tests tests/tests.cpp)
target_link_libraries(tests gtest gtest_main)
target_include_directories(tests PRIVATE include)

add_test(NAME AVLTreeTests COMMAND tests)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
