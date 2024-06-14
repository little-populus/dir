cmake_minimum_required(VERSION 3.20)

project(dir)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
include_directories(header)

add_executable(exec main.cpp)
add_library(lib OBJECT unit.cpp parser.cpp evaluator.cpp queue.cpp)
target_link_libraries(exec lib)
