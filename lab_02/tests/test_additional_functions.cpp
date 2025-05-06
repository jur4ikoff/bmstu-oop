#include "vector.h"
#include <gtest/gtest.h>
#include <math.h>

#define MY_EXCEPT_THROW(func, err_name) \
    try                                 \
    {                                   \
        func;                           \
        FAIL();                         \
    }                                   \
    catch (const err_name &)            \
    {                                   \
        SUCCEED();                      \
    }                                   \
    catch (...)                         \
    {                                   \
        FAIL();                         \
    }

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

TEST(test_normalization, test_null_vec)
{
    Vector<int> vec = { 0, 0, 0 };
    MY_EXCEPT_THROW(vec.normalization(), errDivisionZero)
}

TEST(test_normalization, test_one_vec)
{
    Vector<int> vec = { 0, 1, 0 };
    Vector<int> res = vec;
    vec.normalization();
    // MY_EXCEPT_THROW(vec.normalization(), errDivisionZero)

    EXPECT_EQ(vec.size(), res.size());
    for (int i = 0; i < res.size(); i++)
    {
        EXPECT_EQ(vec[i], res[i]);
    }
}

TEST(test_normalization, test_two_axis_vec)
{
    Vector<int> vec = { 2, 1 };
    Vector<double> expect = { 2 / std::sqrt(5), 1 / std::sqrt(5) };
    auto res = vec.normalization();

    EXPECT_EQ(res.size(), expect.size());
    for (int i = 0; i < expect.size(); i++)
    {
        EXPECT_EQ(res[i], expect[i]);
    }
}

TEST(test_normalization, test_three_axis_vec)
{
    Vector<float> vec = { 2.0, 1.0, 8.0 };
    Vector<float> expect = { (2 / std::sqrt(69)), 1 / std::sqrt(69), 8 / std::sqrt(69) };
    auto res = vec.normalization();

    EXPECT_EQ(res.size(), expect.size());
    for (int i = 0; i < expect.size(); i++)
    {
        EXPECT_EQ(res[i], expect[i]);
    }
}