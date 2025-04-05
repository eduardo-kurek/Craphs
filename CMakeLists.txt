cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20) # for concepts use
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Craphs)

add_executable(Main main.cpp)
target_include_directories(Main PRIVATE "include")

file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(Main PRIVATE ${SOURCES})