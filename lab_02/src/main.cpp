#include "gtest/gtest.h"

#include "test.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    test();
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}