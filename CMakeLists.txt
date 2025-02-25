cmake_minimum_required(VERSION 3.13)
project(LongNumber)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)
