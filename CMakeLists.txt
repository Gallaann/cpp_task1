cmake_minimum_required(VERSION 3.24)
project(Task1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Task1 main.cpp)

add_library(title_by_character_finder src/title_by_character_finder.cpp)

target_include_directories(title_by_character_finder PUBLIC include)

target_link_libraries(Task1 title_by_character_finder)
