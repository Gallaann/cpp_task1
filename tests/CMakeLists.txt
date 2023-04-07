add_executable(test tests.cpp)

target_link_libraries(test ${LIBRARY_NAME} GTest::gtest_main)
