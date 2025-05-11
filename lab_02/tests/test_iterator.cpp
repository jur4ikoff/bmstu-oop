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

class TestReverseIterator : public BaseVectors, public ::testing::Test
{
};

class TestConstReverseIterator : public BaseVectors, public ::testing::Test
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

TEST_F(TestIterator, test_add_commutative)
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

TEST_F(TestIterator, test_add_default)
{
    auto iter = int_vec.begin();
    auto iter_1 = iter + 2;

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

TEST_F(TestConstIterator, test_add)
{
    VectorConstIterator<int> iter = int_vec.cbegin();
    VectorConstIterator<int> iter_1 = 2 + iter;

    while (iter_1 != int_vec.cend())
    {
        std::cout << *iter_1 << " ";
        iter_1++;
    }

    std::cout << std::endl;
}

TEST_F(TestReverseIterator, test_cycle)
{
    auto iter = int_vec.rbegin();

    while (iter != int_vec.rend())
    {
        std::cout << *iter << " ";
        iter++;
    }

    std::cout << std::endl;
}

TEST_F(TestReverseIterator, test_eq)
{
    auto iter = int_vec.rbegin();
    auto iter_1 = iter;

    while (iter_1 != int_vec.rend())
    {
        std::cout << *iter_1 << " ";
        iter_1++;
    }

    std::cout << std::endl;
}

TEST_F(TestReverseIterator, test_add_commutative)
{
    auto iter = int_vec.rbegin();
    auto iter_1 = 2 + iter;

    while (iter_1 != int_vec.rend())
    {
        std::cout << *iter_1 << " ";
        iter_1++;
    }

    std::cout << std::endl;
}

TEST_F(TestReverseIterator, test_add_default)
{
    auto iter = int_vec.rbegin();
    auto iter_1 = iter + 2;

    while (iter_1 != int_vec.rend())
    {
        std::cout << *iter_1 << " ";
        iter_1++;
    }

    std::cout << std::endl;
}

TEST_F(TestReverseIterator, test_add_overflow)
{
    auto iter = int_vec.rbegin();
    auto iter1 = 4 + iter;
    MY_EXPECT_THROW(*iter1, errIndexOutOfRange)
}

TEST_F(TestConstReverseIterator, test_eq)
{
    auto iter = int_vec.rbegin();
    auto iter_1 = iter;

    while (iter_1 != int_vec.rend())
    {
        std::cout << *iter_1 << " ";
        iter_1++;
    }

    std::cout << std::endl;
}

TEST_F(TestConstReverseIterator, test_add_default)
{
    auto iter = int_vec.crbegin();
    auto iter_1 = iter + 2;

    while (iter_1 != int_vec.crend())
    {
        std::cout << *iter_1 << " ";
        iter_1++;
    }

    std::cout << std::endl;
}
