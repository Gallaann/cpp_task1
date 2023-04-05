cmake_minimum_required(VERSION 3.24)
project(Task1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Task1 main.cpp)

add_library(title_by_character_finder src/title_by_character_finder.cpp)

target_include_directories(title_by_character_finder PUBLIC include)

target_link_libraries(Task1 title_by_character_finder)

function(AddValgrind target)
    find_program(VALGRIND_PATH valgrind REQUIRED)
    add_custom_target(valgrind
            COMMAND ${VALGRIND_PATH} --leak-check=yes
            $<TARGET_FILE:${target}>
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
endfunction()

if(WITH_VALGRIND)
    find_program(VALGRIND_PATH valgrind REQUIRED)
    add_custom_target(valgrind
            COMMAND ${VALGRIND_PATH} --leak-check=yes --tool=memcheck
            $<TARGET_FILE:${target}>
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            )
endif()
