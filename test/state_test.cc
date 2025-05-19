#include <gtest/gtest.h>

#include "../src/matrix.h"
#include "../src/state.h"

TEST(StateTest, InitAllFalse)
{
    Matrix<bool> m(7, 6);
    State s(m);
    EXPECT_EQ(-3, s.YOffset());
    EXPECT_EQ(-2, s.XOffset());
}

TEST(StateTest, InitMargin)
{
    // prepend row
    Matrix<bool> m1(3, 3); // offset (-1,-1)
    m1.Set(0, 1, true);
    State s1(m1);
    EXPECT_EQ(-2, s1.YOffset());
    EXPECT_EQ(-1, s1.XOffset());
    EXPECT_EQ(4, s1.GetMatrix().Rows());
    EXPECT_EQ(3, s1.GetMatrix().Columns());

    // prepend column
    Matrix<bool> m2(3, 3); // offset (-1,-1)
    m2.Set(1, 0, true);
    State s2(m2);
    EXPECT_EQ(-1, s2.YOffset());
    EXPECT_EQ(-2, s2.XOffset());
    EXPECT_EQ(3, s2.GetMatrix().Rows());
    EXPECT_EQ(4, s2.GetMatrix().Columns());

    // apend row
    Matrix<bool> m3(3, 3); // offset (-1,-1)
    m3.Set(2, 1, true);
    State s3(m3);
    EXPECT_EQ(-1, s3.YOffset());
    EXPECT_EQ(-1, s3.XOffset());
    EXPECT_EQ(4, s3.GetMatrix().Rows());
    EXPECT_EQ(3, s3.GetMatrix().Columns());

    // append column
    Matrix<bool> m4(3, 3); // offset (-1,-1)
    m4.Set(1, 2, true);
    State s4(m4);
    EXPECT_EQ(-1, s4.YOffset());
    EXPECT_EQ(-1, s4.XOffset());
    EXPECT_EQ(3, s4.GetMatrix().Rows());
    EXPECT_EQ(4, s4.GetMatrix().Columns());

    // prepend both
    Matrix<bool> m5(3, 3); // offset (-1,-1)
    m5.Set(0, 0, true);
    State s5(m5);
    EXPECT_EQ(-2, s5.YOffset());
    EXPECT_EQ(-2, s5.XOffset());
    EXPECT_EQ(4, s5.GetMatrix().Rows());
    EXPECT_EQ(4, s5.GetMatrix().Columns());

    // append both
    Matrix<bool> m6(3, 3); // offset (-1,-1)
    m6.Set(2, 2, true);
    State s6(m6);
    EXPECT_EQ(-1, s6.YOffset());
    EXPECT_EQ(-1, s6.XOffset());
    EXPECT_EQ(4, s6.GetMatrix().Rows());
    EXPECT_EQ(4, s6.GetMatrix().Columns());
}
