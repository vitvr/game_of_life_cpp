#include <gtest/gtest.h>
#include <stdexcept>
#include <vector>

#include "../src/matrix.h"

TEST(MatrixTest, EmptyInit)
{
    Matrix<bool> empty_default_matrix;
    EXPECT_EQ(std::vector<bool>(), empty_default_matrix.Data());
    EXPECT_EQ(0, empty_default_matrix.Rows());
    EXPECT_EQ(0, empty_default_matrix.Columns());

    Matrix<bool> empty_sized_matrix(0,0);
    EXPECT_EQ(std::vector<bool>(), empty_sized_matrix.Data());
    EXPECT_EQ(0, empty_sized_matrix.Rows());
    EXPECT_EQ(0, empty_sized_matrix.Columns());

    Matrix<bool> empty_sized_list_matrix(0,0, {});
    EXPECT_EQ(std::vector<bool>(), empty_sized_list_matrix.Data());
    EXPECT_EQ(0, empty_sized_list_matrix.Rows());
    EXPECT_EQ(0, empty_sized_list_matrix.Columns());

    // Matrix<bool> empty_init_list_matrix = {};

    // EXPECT_EQ(std::vector<bool>(), empty_init_list_matrix.Data());
    // EXPECT_EQ(0, empty_init_list_matrix.Rows());
    // EXPECT_EQ(0, empty_init_list_matrix.Columns());

    // Matrix<bool> empty_init_lists_matrix = {{true}, {false}};

    // EXPECT_EQ(std::vector<bool>(), empty_init_lists_matrix.Data());
    // EXPECT_EQ(0, empty_init_lists_matrix.Rows());
    // EXPECT_EQ(0, empty_init_lists_matrix.Columns());
}

TEST(MatrixTest, OutOfRangeInit)
{
    EXPECT_ANY_THROW(Matrix<bool> m1(-1, 3));
    EXPECT_ANY_THROW(Matrix<bool> m2(3, -1));

    EXPECT_ANY_THROW(Matrix<bool> m2(2, 3, {true, false}));
}

TEST(MatrixTest, Init)
{
    Matrix<bool> m1(2,3);
    EXPECT_EQ(std::vector<bool>(6), m1.Data());
    EXPECT_EQ(2, m1.Rows());
    EXPECT_EQ(3, m1.Columns());

    Matrix<bool> m2(2,2, {true, false, false, true});
    EXPECT_EQ(std::vector({true, false, false, true}), m2.Data());
}

TEST(MatrixTest, AtGet)
{
    Matrix<int> m1;
    Matrix<int> m2(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    EXPECT_ANY_THROW(m1.At(0, 0));
    EXPECT_ANY_THROW(m2.At(1, 3));

    // edges
    EXPECT_EQ(1, m2.At(0, 0));
    EXPECT_EQ(9, m2.At(2, 2));

    EXPECT_EQ(6, m2.At(1, 2));
}

TEST(MatrixTest, AtSet)
{
    // edge and fail cases on previous test

    Matrix<int> m1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    m1.At(1, 2) = 9;
    EXPECT_EQ(9, m1.At(1, 2));
}

TEST(MatrixTest, GetRow)
{
    Matrix<int> m1(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_ANY_THROW(m1.GetRow(-1));
    EXPECT_ANY_THROW(m1.GetRow(2));
    EXPECT_EQ(std::vector<int>({1, 2, 3}), m1.GetRow(0));
    EXPECT_EQ(std::vector<int>({4, 5, 6}), m1.GetRow(1));

    // possible future behaviour, get row by ref not by val
    // m1.GetRow(1).at(1) = 0;
    // EXPECT_EQ(std::vector<int>({4, 0, 6}), m1.GetRow(1));

}


TEST(MatrixTest, GetColumn)
{
    Matrix<int> m1(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_ANY_THROW(m1.GetColumn(-1));
    EXPECT_ANY_THROW(m1.GetColumn(3));
    EXPECT_EQ(std::vector<int>({1, 4}), m1.GetColumn(0));
    EXPECT_EQ(std::vector<int>({2, 5}), m1.GetColumn(1));
    EXPECT_EQ(std::vector<int>({3, 6}), m1.GetColumn(2));
}

TEST(MatrixTest, InsertRow)
{
    Matrix<int> m(2, 3, {1, 2, 3, 4, 5, 6});
    // valid rows
    std::vector<int> row1 = {-2, -1, 0};
    std::vector<int> row2 = {7, 8, 9};

    // invalid rows
    std::vector<int> row3 = {7, 8};
    std::vector<int> row4 = {7, 8, 9, 10};

    // resulting matrices
    std::vector<int> v1 = {-2, -1, 0, 1, 2, 3, 4, 5, 6};
    std::vector<int> v2 = {-2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_THROW(m.InsertRow(-1, row1), std::out_of_range);
    EXPECT_THROW(m.InsertRow(3, row2), std::out_of_range);
    EXPECT_THROW(m.InsertRow(1, row3), std::length_error);
    EXPECT_THROW(m.InsertRow(1, row4), std::length_error);

    m.InsertRow(0, row1);
    EXPECT_EQ(3, m.Rows());
    EXPECT_EQ(v1, m.Data());

    m.InsertRow(3, row2);
    EXPECT_EQ(4, m.Rows());
    EXPECT_EQ(v2, m.Data());
}
