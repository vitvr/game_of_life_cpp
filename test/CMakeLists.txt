enable_testing()

add_executable(hello_test hello_test.cc)
add_executable(matrix_test matrix_test.cc)

target_link_libraries(hello_test GTest::gtest_main)
target_link_libraries(matrix_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(hello_test)
gtest_discover_tests(matrix_test)
