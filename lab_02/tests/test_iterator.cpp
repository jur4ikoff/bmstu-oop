#include "constants.hpp"
#include "test_base.hpp"
#include "vector.hpp"

#include <gtest/gtest.h>

class TestIterator : public BaseVectors, public ::testing::Test
{
};

TEST_F(TestIterator, test_cycle)
{
    auto iter = int_vec.begin();

    while (iter != int_vec.end())
    {
        std::cout << *iter << " ";
        iter++;
    }

    std::cout << std::endl;
}

TEST_F(TestIterator, test_eq)
{
    auto iter = int_vec.begin();
    auto iter_1 = iter;

    while (iter_1 != int_vec.end())
    {
        std::cout << *iter_1 << " ";
        iter_1++;
    }

    std::cout << std::endl;
}

TEST_F(TestIterator, test_add)
{
    auto iter = int_vec.begin();
    auto iter_1 = 2 + iter;

    while (iter_1 != int_vec.end())
    {
        std::cout << *iter_1 << " ";
        iter_1++;
    }

    std::cout << std::endl;
}

TEST_F(TestIterator, test_add_overflow)
{
    auto iter = int_vec.begin();
    auto iter1 = 4 + iter;
    MY_EXPECT_THROW(*iter1, errIndexOutOfRange)
}
