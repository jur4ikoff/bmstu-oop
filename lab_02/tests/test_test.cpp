#include "vector.hpp"
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

TEST(MyCodeTest, test_pos)
{
    Vector<int> a = { -100, -4, 5 };
    // Vector<int> b = { 2, 2, 2 };

    // Vector<int> res(a + b);

    // int expect[3] = { -98, -2, 7 };
    // int i = 0;
    // for (auto el : res)
    // {
    //     EXPECT_EQ(el, expect[i++]);
    // }
}

// int main(int argc, char **argv)
// {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
