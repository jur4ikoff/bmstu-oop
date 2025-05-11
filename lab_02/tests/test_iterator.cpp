#include "constants.hpp"
#include "test_base.hpp"
#include "vector.hpp"

#include <gtest/gtest.h>

class TestIterator : public BaseVectors, public ::testing::Test
{
};

class TestConstIterator : public BaseVectors, public ::testing::Test
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

TEST_F(TestConstIterator, test_cycle)
{
    VectorConstIterator<int> iter = int_vec.begin();

    while (iter != int_vec.end())
    {
        std::cout << *iter << " ";
        iter++;
    }

    std::cout << std::endl;
}

TEST_F(TestConstIterator, test_eq)
{
    VectorConstIterator<int> iter = int_vec.begin();
    VectorConstIterator<int> iter_1 = iter;

    while (iter_1 != int_vec.end())
    {
        std::cout << *iter_1 << " ";
        iter_1++;
    }

    std::cout << std::endl;
}

TEST_F(TestConstIterator, test_add)
{
    VectorConstIterator<int> iter = int_vec.begin();
    VectorConstIterator<int> iter_1 = 2 + iter;

    while (iter_1 != int_vec.end())
    {
        std::cout << *iter_1 << " ";
        iter_1++;
    }

    std::cout << std::endl;
}

TEST_F(TestConstIterator, test_add_overflow)
{
    VectorConstIterator<int> iter = int_vec.begin();
    VectorConstIterator<int> iter1 = 4 + iter;
    MY_EXPECT_THROW(*iter1, errIndexOutOfRange)
}
