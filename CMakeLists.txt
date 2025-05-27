cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20) # for concepts use
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-g)

project(Craphs)
add_subdirectory(extern/tinyxml2)

file(GLOB_RECURSE SOURCES src/*.cpp)
add_library(craphs STATIC ${SOURCES})
target_include_directories(craphs PUBLIC "include" "${CMAKE_SOURCE_DIR}/extern/tinyxml2")
target_link_libraries(craphs PRIVATE tinyxml2)

add_executable(Main main.cpp)
target_link_libraries(Main PRIVATE craphs)