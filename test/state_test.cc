#include <gtest/gtest.h>

#include "../src/matrix.h"
#include "../src/state.h"

TEST(StateTest, Init)
{
    Matrix<bool> m(7, 6);
    State s(m);
    EXPECT_EQ(-3, s.YOffset());
    EXPECT_EQ(-2, s.XOffset());
}
