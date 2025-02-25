cmake_minimum_required(VERSION 3.13)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_library(LongNumber STATIC LongNumber.cpp LongNumber.h Helpers.cpp Helpers.h)

target_include_directories(LongNumber PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(pi pi.cpp)
target_link_libraries(pi PRIVATE LongNumber)