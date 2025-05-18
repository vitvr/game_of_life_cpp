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
    Matrix<bool> m(3, 3); // offset (-1,-1)
    m.Set(0, 1, true);
    State s(m);
    EXPECT_EQ(-2, s.YOffset());
    EXPECT_EQ(-1, s.XOffset());
}
