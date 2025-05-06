#include <gtest/gtest.h>
#include "vector.h"

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
    Vector<int> vec = {1};
    EXPECT_EQ(vec.len(), 1);
}

TEST(test_len, test_two_axis_vector)
{
    // Проверка на пустой вектор
    Vector<int> vec = {3, 4};
    EXPECT_EQ(vec.len(), 5);
}

TEST(test_len, test_many_axis_vector)
{
    // Проверка на пустой вектор
    Vector<double> vec = {1.2, 4.5, 5.4, 2.2, 10.1};
    EXPECT_EQ(static_cast<float>(vec.len()), 12.5578661f);
}

TEST(test_normalization, test_null_vec)
{
    Vector<int> vec = {0, 0, 0};
    auto res_vector = vec.normalization();
}
