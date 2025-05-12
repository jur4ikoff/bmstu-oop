#include "constants.hpp"
#include "test_base.hpp"
#include "vector.h"

#include <gtest/gtest.h>

TEST(test_normalization, test_null_vec)
{
    Vector<int> vec = {0, 0, 0};
    MY_EXPECT_THROW(vec.normalization(), errDivisionZero)
}

TEST(test_normalization, test_one_vec)
{
    Vector<int> vec = {0, 1, 0};
    Vector<int> res(vec);
    vec.normalization();

    EXPECT_EQ(vec.size(), res.size());
    for (int i = 0; i < res.size(); i++)
    {
        EXPECT_EQ(vec[i], res[i]);
    }
}

TEST(test_normalization, test_two_axis_vec)
{
    Vector<int> vec = {2, 1};
    Vector<double> expect = {2 / std::sqrt(5), 1 / std::sqrt(5)};
    auto res = vec.normalization();

    EXPECT_EQ(res.size(), expect.size());
    for (int i = 0; i < expect.size(); i++)
    {
        EXPECT_EQ(res[i], expect[i]);
    }
}

TEST(test_normalization, test_three_axis_vec)
{
    Vector<float> vec = {2.0, 1.0, 8.0};
    Vector<float> expect = {(2 / std::sqrt(69)), 1 / std::sqrt(69), 8 / std::sqrt(69)};
    auto res = vec.normalization();

    EXPECT_EQ(res.size(), expect.size());
    for (int i = 0; i < expect.size(); i++)
    {
        EXPECT_EQ(res[i], expect[i]);
    }
}

TEST(test_is_normalize, no_vector)
{
    Vector<int> vec;
    MY_EXPECT_THROW(vec.is_normalize(), errNegSize)
}

TEST(test_is_normalize, null_vector)
{
    Vector<int> vec = {0, 0, 0, 0};
    bool expected = false;

    bool res = vec.is_normalize();
    EXPECT_EQ(res, expected);
}

TEST(test_is_normalize, not_normalize_vector)
{
    Vector<int> vec = {2, 4, 1, 3};
    bool expected = false;

    bool res = vec.is_normalize();
    EXPECT_EQ(res, expected);
}

TEST(test_is_normalize, normalize_vector)
{
    Vector<int> vec = {1, 0, 0, 0};
    bool expected = true;

    bool res = vec.is_normalize();
    EXPECT_EQ(res, expected);
}

TEST(test_is_zero, none_vector)
{
    Vector<int> vec;
    MY_EXPECT_THROW(vec.is_zero(), errNegSize)
}

TEST(test_is_zero, zero_vector)
{
    Vector<int> vec = {0, 0, 0, 0};
    bool expected = true;

    bool res = vec.is_zero();
    EXPECT_EQ(res, expected);
}

TEST(test_is_zero, not_zero_vector)
{
    Vector<int> vec = {1, 2, 3, 4};
    bool expected = false;

    bool res = vec.is_zero();
    EXPECT_EQ(res, expected);
}

TEST(test_calc_angle, null_vector)
{
    Vector<double> v1({1.0, 0.0});
    Vector<double> v2({0.0, 0.0});
    MY_EXPECT_THROW(v1.calc_angle(v2), errDivisionZero)
}

TEST(test_calc_angle, calc_angle_90)
{
    Vector<double> v1({1.0, 0.0});
    Vector<double> v2({0.0, 1.0});
    EXPECT_NEAR(v1.calc_angle(v2), 90.0, EPS);
}

TEST(test_calc_angle, calc_angle_difference_type)
{
    Vector<double> v1({1.0, 0.0});
    Vector<int> v2({0, 1});
    EXPECT_NEAR(v1.calc_angle(v2), 90.0, EPS);
}

TEST(test_calc_angle, parallel_vectors)
{
    Vector<double> v1({1.0, 1.0});
    Vector<double> v2({2.0, 2.0});

    EXPECT_NEAR(v1.calc_angle(v2), 0.0, EPS);
}

TEST(test_calc_angle, _45_degrees_vectors)
{
    Vector<double> v1({1.0, 0.0});
    Vector<double> v2({1.0, 1.0});

    EXPECT_NEAR(v1.calc_angle(v2), 45.0, EPS);
}