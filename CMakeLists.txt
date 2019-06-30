cmake_minimum_required(VERSION 3.10)
set(TARGET sorttester)
project(${TARGET})

enable_language(C CXX)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -O0 -g -pthread")

include_directories(.)

set(SOURCE ./src/main.cpp)
add_subdirectory(./src)

add_executable(${TARGET} ${SOURCE} ${HEADERS})