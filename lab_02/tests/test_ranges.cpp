#include "constants.hpp"
#include "test_base.hpp"
#include "vector.h"

#include <algorithm>
#include <cassert>
#include <gtest/gtest.h>
#include <ranges>

class TestRanges : public BaseVectors, public ::testing::Test
{
};

TEST_F(TestRanges, ranges_asserts)
{
    static_assert(std::ranges::range<Vector<int>>, "Vector<T> is not a range!");

    static_assert(
        std::random_access_iterator<typename Vector<char>::iterator>,
        "Vector<T>::iterator must be a random_access_iterator");

    static_assert(
        std::random_access_iterator<typename Vector<int>::const_iterator>,
        "Vector<T>::const_iterator must be a random_access_iterator");

    static_assert(
        std::random_access_iterator<typename Vector<int>::reverse_iterator>,
        "Vector<T>::const_iterator must be a random_access_iterator");

    static_assert(
        std::random_access_iterator<typename Vector<int>::const_reverse_iterator>,
        "Vector<T>::const_iterator must be a random_access_iterator");

    static_assert(
        std::is_same_v<typename Vector<int>::value_type, int>, "Vector<T>::value_type must be T");
    static_assert(
        std::is_same_v<typename Vector<int>::reference, int &>, "Vector<T>::reference must be T&");

    static_assert(
        std::ranges::output_range<Vector<int>, int>,
        "Vector<T> must be an output range (support element assignment)");

    assert(std::ranges::size(int_vec) == int_vec.size());
}

TEST_F(TestRanges, test_binary_search)
{
    assert(std::is_sorted(int_vec.begin(), int_vec.end()));
    bool rc = std::binary_search(int_vec.begin(), int_vec.end(), 4);
    EXPECT_EQ(rc, true);
}