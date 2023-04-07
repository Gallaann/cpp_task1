set(TEST_NAME finder_test)
add_executable(${TEST_NAME} tests.cpp)
target_link_libraries(${TEST_NAME} gtest_main)

target_link_libraries(${TEST_NAME} ${LIBRARY_NAME} GTest::gtest_main)

add_test(NAME finder_test COMMAND ${TEST_NAME})
