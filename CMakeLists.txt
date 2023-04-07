cmake_minimum_required(VERSION 3.24)
set(PROJECT_NAME cpp_task1)
project(${PROJECT_NAME}
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

#add_subdirectory(include)
add_subdirectory(src)

set (MAIN main.cpp)
add_executable(${PROJECT_NAME} ${MAIN})

set(LIBRARY_NAME finder)
target_include_directories(${LIBRARY_NAME} PUBLIC include)

target_link_libraries (${PROJECT_NAME} ${LIBRARY_NAME})

option(BUILD_TESTS "build tests")
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()

#function(AddValgrind target)
#    find_program(VALGRIND_PATH valgrind REQUIRED)
#    add_custom_target(valgrind
#            COMMAND ${VALGRIND_PATH} --leak-check=yes
#            $<TARGET_FILE:${target}>
#            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#            )
#endfunction()
#
#if(WITH_VALGRIND)
#    find_program(VALGRIND_PATH valgrind REQUIRED)
#    add_custom_target(valgrind
#            COMMAND ${VALGRIND_PATH} --leak-check=yes --tool=memcheck
#            $<TARGET_FILE:${target}>
#            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#            )
#endif()
