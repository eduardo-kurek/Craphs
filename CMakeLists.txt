cmake_minimum_required(VERSION 3.10)
project(Craphs)

add_executable(Main main.cpp)
target_include_directories(Main PRIVATE "include")

file(GLOB_RECURSE SOURCES src/*.cpp)
target_sources(Main PRIVATE ${SOURCES})