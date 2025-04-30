#include "gtest/gtest.h"

int add(int a, int b)
{
    return a + b;
}

TEST(MyCodeTest, BasicTest)
{
    EXPECT_EQ(2, add(1, 1));
}

TEST(MyCodeTest, NegativeTest)
{
    EXPECT_EQ(-1, add(-2, 1));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}