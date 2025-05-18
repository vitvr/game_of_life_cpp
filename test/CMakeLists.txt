enable_testing()

add_executable(matrix_test matrix_test.cc)

target_link_libraries(matrix_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(matrix_test)
