enable_testing()

add_executable(matrix_test matrix_test.cc)
add_executable(state_test state_test.cc ../src/state.cc)

target_link_libraries(matrix_test GTest::gtest_main)
target_link_libraries(state_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(matrix_test)
gtest_discover_tests(state_test)
