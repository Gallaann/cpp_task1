cmake_minimum_required(VERSION 3.24)
set(PROJECT_NAME cpp_task1)
project(${PROJECT_NAME}
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(--coverage)
add_link_options(--coverage)

add_subdirectory(src)

set (MAIN main.cpp)
add_executable(${PROJECT_NAME} ${MAIN})

set(LIBRARY_NAME finder)
target_include_directories(${LIBRARY_NAME} PUBLIC include)

target_link_libraries (${PROJECT_NAME} ${LIBRARY_NAME})

option(BUILD_TESTS "build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()

#option(WITH_VALGRIND "build with valgrind")
#set(WITH_VALGRIND ON)
#if(WITH_VALGRIND)
##    include(CTest)
#    enable_testing()
##    find_program(VALGRIND_PATH valgrind REQUIRED)
#    add_test(NAME valgrind
#            COMMAND valgrind
##            --error-exitcode=1
#            --tool=memcheck
#            --leak-check=full
##            --errors-for-leak-kinds=definite
#            --show-leak-kinds=all
#            $<TARGET_FILE:${PROJECT_NAME}>
##            $<TARGET_FILE:finder_test>
#            WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
#endif()
