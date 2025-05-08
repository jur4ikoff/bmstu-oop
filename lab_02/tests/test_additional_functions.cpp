#include "test_base.hpp"
#include "vector.h"

#include <gtest/gtest.h>
#include <math.h>

TEST(test_len, test_empty_vector)
{
    // Проверка на пустой вектор
    // Должно выкинуть исключение
    Vector<int> vec;
    MY_EXCEPT_THROW(vec.len(), errNegSize)
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

TEST(scalar_mul, null_vector)
{
    Vector<int> vec1 = { 1, 2, 3 };
    Vector<int> vec2;
    MY_EXCEPT_THROW(vec1 & vec2, errNegSize)
}

TEST(scalar_mul, vector_different_size)
{
    Vector<int> vec1 = { 1, 2, 3 };
    Vector<int> vec2 = { 0, 0, 0, 0 };
    MY_EXCEPT_THROW(vec1 & vec2, errVectorsSizeNotEqual)
}

TEST(scalar_mul, zero_vector)
{
    Vector<int> vec1 = { 1, 2, 3 };
    Vector<int> vec2 = { 0, 0, 0 };

    EXPECT_EQ(vec1 & vec2, 0);
}

TEST(scalar_mul, int_vectors)
{
    Vector<int> v1({ 1, 2, 3 });
    Vector<int> v2({ 4, 5, 6 });
    EXPECT_EQ(v1 & v2, 1 * 4 + 2 * 5 + 3 * 6);
}

TEST(scalar_mul, commutative_operation)
{
    Vector<double> v1({ 1.1, 2.2, 3.3 });
    Vector<double> v2({ 4.4, 5.5, 6.6 });

    auto result1 = v1 & v2;
    auto result2 = v2 & v1;

    EXPECT_NEAR(result1, result2, EPS);
}

TEST(scalar_mul, double_vectors)
{
    Vector<double> v1({ 1.1, 2.2, 3.3 });
    Vector<double> v2({ 4.4, 5.5, 6.6 });

    auto result1 = v1 & v2;

    EXPECT_NEAR(result1, 1.1 * 4.4 + 2.2 * 5.5 + 3.3 * 6.6, EPS);
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
