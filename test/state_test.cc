#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "../src/matrix.h"
#include "../src/state.h"

TEST(StateTest, InitAllFalse)
{
    Matrix<bool> m(7, 6);
    State s(m);
    EXPECT_EQ(-3, s.YOffset());
    EXPECT_EQ(-2, s.XOffset());
}

TEST(StateTest, InitEmpty)
{
    Matrix<bool> m;
    State s(m);
    EXPECT_EQ(std::vector<bool>({false, false, false, false}), s.GetMatrix().Data());
    EXPECT_EQ(2, s.Rows());
    EXPECT_EQ(2, s.Columns());
}

// TEST(StateTest, InitSmall)
// {
//     // matrix should be resized to at least 2x2 if smaller
//     Matrix<bool> m();
//     State s(m);
//     EXPECT_EQ(std::vector<bool>({false, false, false, false}), s.GetMatrix().Data());
//     EXPECT_EQ(2, s.Rows());
//     EXPECT_EQ(2, s.Columns());
// }

TEST(StateTest, InitMargin)
{
    // prepend  2 rows, 1 column
    // append   1 row , 2 columns
    Matrix<bool> m1(2, 2); // offset (0, 0)
    m1.Set(0, 1, true);
    State s1(m1);
    EXPECT_EQ(-2, s1.YOffset());
    EXPECT_EQ(-1, s1.XOffset());
    EXPECT_EQ(5, s1.GetMatrix().Rows());
    EXPECT_EQ(5, s1.GetMatrix().Columns());

    // prepend  1 row , 2 columns
    // apepend  2 rows, 1 column
    Matrix<bool> m2(2, 2); // offset (0, 0)
    m2.Set(1, 0, true);
    State s2(m2);
    EXPECT_EQ(-1, s2.YOffset());
    EXPECT_EQ(-2, s2.XOffset());
    EXPECT_EQ(5, s2.GetMatrix().Rows());
    EXPECT_EQ(5, s2.GetMatrix().Columns());

    // // from when margin was 1 (now 2)
    // // prepend columns
    // Matrix<bool> m2(3, 3); // offset (-1,-1)
    // m2.Set(1, 0, true);
    // State s2(m2);
    // EXPECT_EQ(-1, s2.YOffset());
    // EXPECT_EQ(-3, s2.XOffset());
    // EXPECT_EQ(3, s2.GetMatrix().Rows());
    // EXPECT_EQ(5, s2.GetMatrix().Columns());

    // // apend rows
    // Matrix<bool> m3(3, 3); // offset (-1,-1)
    // m3.Set(2, 1, true);
    // State s3(m3);
    // EXPECT_EQ(-1, s3.YOffset());
    // EXPECT_EQ(-1, s3.XOffset());
    // EXPECT_EQ(5, s3.GetMatrix().Rows());
    // EXPECT_EQ(3, s3.GetMatrix().Columns());

    // // append columns
    // Matrix<bool> m4(3, 3); // offset (-1,-1)
    // m4.Set(1, 2, true);
    // State s4(m4);
    // EXPECT_EQ(-1, s4.YOffset());
    // EXPECT_EQ(-1, s4.XOffset());
    // EXPECT_EQ(3, s4.GetMatrix().Rows());
    // EXPECT_EQ(5, s4.GetMatrix().Columns());

    // // prepend both
    // Matrix<bool> m5(3, 3); // offset (-1,-1)
    // m5.Set(0, 0, true);
    // State s5(m5);
    // EXPECT_EQ(-3, s5.YOffset());
    // EXPECT_EQ(-3, s5.XOffset());
    // EXPECT_EQ(5, s5.GetMatrix().Rows());
    // EXPECT_EQ(5, s5.GetMatrix().Columns());

    // // append both
    // Matrix<bool> m6(3, 3); // offset (-1,-1)
    // m6.Set(2, 2, true);
    // State s6(m6);
    // EXPECT_EQ(-1, s6.YOffset());
    // EXPECT_EQ(-1, s6.XOffset());
    // EXPECT_EQ(5, s6.GetMatrix().Rows());
    // EXPECT_EQ(5, s6.GetMatrix().Columns());
}

TEST(StateTest, StepTest)
{
    //glider
    Matrix<bool> m1(7, 7, {
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0,
        0, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0 
    });

    // next stage of glider
    // all rules are applied making it
    Matrix<bool> m2(8, 7, {
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 1, 0, 0,
        0, 0, 0, 1, 1, 0, 0,
        0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0
    });

    State s(m1);
    s.Step();

    std::vector<bool> v = s.GetMatrix().Data();
    for (bool e : v)
        std::cerr << e;

    std::cerr << '\n';

    std::cerr << "rows: " << s.Rows() << '\n';
    std::cerr << "columns: " << s.Columns() << '\n';

    for (int i = 0; i != s.Rows(); ++i)
    {
        for (int j = 0; j != s.Columns(); ++j)
        {
            std::cerr << "row: " << i << '\n';
            std::cerr << "column: " << j << '\n';
            std::cerr << s.GetMatrix().Get(i, j) << '\n';
        }
    }

    ASSERT_EQ(m2.Data(), s.GetMatrix().Data());
}
