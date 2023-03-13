cmake_minimum_required(VERSION 3.24)
project(Task1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Task1 main.cpp)

add_library(movie_id_finder src/movie_id_finder.cpp)

target_include_directories(movie_id_finder PUBLIC include)

target_link_libraries(Task1 movie_id_finder)
