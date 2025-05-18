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

TEST(MatrixTest, Get)
{
    Matrix<int> m1;
    Matrix<int> m2(5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
    EXPECT_ANY_THROW(m1.Get(0, 0));
    EXPECT_ANY_THROW(m2.Get(5, 1));
    EXPECT_ANY_THROW(m2.Get(1, 3));

    // edges
    EXPECT_EQ(1, m2.Get(0, 0));
    EXPECT_EQ(15, m2.Get(4, 2));

    EXPECT_EQ(8, m2.Get(2, 1));
    EXPECT_EQ(11, m2.Get(3, 1));
}

TEST(MatrixTest, Set)
{
    // edge and fail cases on previous test
    Matrix<int> m1;
    Matrix<int> m2(5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
    EXPECT_ANY_THROW(m1.Set(0, 0, 0));
    EXPECT_ANY_THROW(m2.Set(5, 1, 0));
    EXPECT_ANY_THROW(m2.Set(1, 3, 0));

    // edges
    m2.Set(0, 0, -1);
    EXPECT_EQ(-1, m2.Get(0, 0));
    m2.Set(4, 2, -2);
    EXPECT_EQ(-2, m2.Get(4, 2));
    
    m2.Set(1, 1, -3);
    EXPECT_EQ(-3, m2.Get(1, 1));

    // Matrix<int> m1(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    // m1.Set(1, 2, 9);
    // EXPECT_EQ(9, m1.Get(1, 2));
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

TEST(MatrixTest, InsertColumn)
{
    Matrix<int> m(2, 3, {1, 2, 3, 4, 5, 6});
    // valid columns
    std::vector<int> column0 = {-1, -2};
    std::vector<int> column1 = {10, 20};
    std::vector<int> column2 = {30, 40};

    // invalid columns
    std::vector<int> column3 = {10};
    std::vector<int> column4 = {10, 20, 30};

    // resulting matrices
    std::vector<int> v1 = {10, 1, 2, 3, 20, 4, 5, 6};
    std::vector<int> v2 = {10, 1, 2, 3, 30, 20, 4, 5, 6, 40};
    std::vector<int> v0 = {10, 1, -1,  2, 3, 30, 20, 4, -2, 5, 6, 40};

    EXPECT_THROW(m.InsertColumn(-1, column1), std::out_of_range);
    EXPECT_THROW(m.InsertColumn(4, column2), std::out_of_range);
    EXPECT_THROW(m.InsertColumn(1, column3), std::length_error);
    EXPECT_THROW(m.InsertColumn(1, column4), std::length_error);

    m.InsertColumn(0, column1);
    EXPECT_EQ(4, m.Columns());
    EXPECT_EQ(v1, m.Data());

    m.InsertColumn(4, column2);
    EXPECT_EQ(5, m.Columns());
    EXPECT_EQ(v2, m.Data());

    m.InsertColumn(2, column0);
    EXPECT_EQ(6, m.Columns());
    EXPECT_EQ(v0, m.Data());
}

TEST(MatrixTest, RemoveRow)
{
    Matrix<int> m(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

    EXPECT_ANY_THROW(m.RemoveRow(-1));
    EXPECT_ANY_THROW(m.RemoveRow(4));

    std::vector<int> v1 = {4, 5, 6, 7, 8, 9, 10, 11, 12};
    std::vector<int> v2 = {4, 5, 6, 10, 11, 12};
    std::vector<int> v3 = {4, 5, 6};

    // first
    m.RemoveRow(0);
    EXPECT_EQ(3, m.Rows());
    EXPECT_EQ(v1, m.Data());

    // middle
    m.RemoveRow(1);
    EXPECT_EQ(2, m.Rows());
    EXPECT_EQ(v2, m.Data());

    // last
    m.RemoveRow(1);
    EXPECT_EQ(1, m.Rows());
    EXPECT_EQ(v3, m.Data());
}

TEST(MatrixTest, RemoveColumn)
{
    Matrix<int> m(3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

    EXPECT_ANY_THROW(m.RemoveColumn(-1));
    EXPECT_ANY_THROW(m.RemoveColumn(4));

    std::vector<int> v1 = {2, 3, 4, 6, 7, 8, 10, 11, 12};
    std::vector<int> v2 = {2, 4, 6, 8, 10, 12};
    std::vector<int> v3 = {2, 6, 10};

    // first
    m.RemoveColumn(0);
    EXPECT_EQ(3, m.Columns());
    EXPECT_EQ(v1, m.Data());

    // middle
    m.RemoveColumn(1);
    EXPECT_EQ(2, m.Columns());
    EXPECT_EQ(v2, m.Data());

    // last
    m.RemoveColumn(1);
    EXPECT_EQ(1, m.Columns());
    EXPECT_EQ(v3, m.Data());
}

TEST(MatrixTest, GetSubRow)
{
    Matrix<int> m1(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_ANY_THROW(m1.GetSubRow(-1, 1, 1));
    EXPECT_ANY_THROW(m1.GetSubRow(2, 1, 1));
    EXPECT_ANY_THROW(m1.GetSubRow(1, -1, 1));
    EXPECT_ANY_THROW(m1.GetSubRow(1, 3, 1));
    EXPECT_ANY_THROW(m1.GetSubRow(1, 1, -1));
    EXPECT_ANY_THROW(m1.GetSubRow(1, 1, 3));

    // edge
    EXPECT_EQ(std::vector<int>({1, 2, 3}), m1.GetSubRow(0, 0, 3));
    EXPECT_EQ(std::vector<int>(), m1.GetSubRow(0, 0, 0));

    EXPECT_EQ(std::vector<int>({2, 3}), m1.GetSubRow(0, 1, 2));
    EXPECT_EQ(std::vector<int>({1, 2}), m1.GetSubRow(0, 0, 2));
    EXPECT_EQ(std::vector<int>({5, 6}), m1.GetSubRow(1, 1, 2));
}

TEST(MatrixTest, GetSubColumn)
{
    Matrix<int> m1(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    EXPECT_ANY_THROW(m1.GetSubColumn(-1, 1, 1));
    EXPECT_ANY_THROW(m1.GetSubColumn(3, 1, 1));
    EXPECT_ANY_THROW(m1.GetSubColumn(1, -1, 1));
    EXPECT_ANY_THROW(m1.GetSubColumn(1, 4, 1));
    EXPECT_ANY_THROW(m1.GetSubColumn(1, 1, -1));
    EXPECT_ANY_THROW(m1.GetSubColumn(1, 1, 4));

    // edge
    EXPECT_EQ(std::vector<int>({1, 4, 7, 10}), m1.GetSubColumn(0, 0, 4));
    EXPECT_EQ(std::vector<int>(), m1.GetSubColumn(0, 0, 0));

    EXPECT_EQ(std::vector<int>({1, 4}), m1.GetSubColumn(0, 0, 2));
    EXPECT_EQ(std::vector<int>({5, 8}), m1.GetSubColumn(1, 1, 2));
    EXPECT_EQ(std::vector<int>({9}), m1.GetSubColumn(2, 2, 1));
}
