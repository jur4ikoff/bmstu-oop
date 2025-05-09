#include "test_base.hpp"
#include "vector.h"

#include <gtest/gtest.h>
#include <math.h>

TEST(test_len, test_empty_vector)
{
    // Проверка на пустой вектор
    // Должно выкинуть исключение
    Vector<int> vec;
    MY_EXPECT_THROW(vec.len(), errNegSize)
}

TEST(test_len, test_one_axis_vector)
{
    // Проверка на пустой вектор
    // Должно выкинуть исключение
    Vector<int> vec = { 1 };
    EXPECT_EQ(vec.len(), 1);
}

TEST(test_len, test_two_axis_vector)
{
    // Проверка на пустой вектор
    Vector<int> vec = { 3, 4 };
    EXPECT_EQ(vec.len(), 5);
}

TEST(test_len, test_many_axis_vector)
{
    // Проверка на пустой вектор
    Vector<double> vec = { 1.2, 4.5, 5.4, 2.2, 10.1 };
    EXPECT_EQ(static_cast<float>(vec.len()), 12.5578661f);
}

TEST(set_item, pos)
{
    Vector<int> vec(3);
    vec.set_item(0, 10);
    vec.set_item(1, 20);
    vec.set_item(2, 30);

    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);
}
