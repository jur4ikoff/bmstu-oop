#pragma once

#include "vector.h"

#include <type_traits>

#define MY_EXPECT_THROW(func, err_name) \
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

template <typename T, typename = void>
struct is_vector_constructible : std::false_type
{
};

template <typename T>
struct is_vector_constructible<T,
                               std::void_t<decltype(Vector<T>{})>> : std::true_type
{
};

class BaseVectors
{
protected:
    Vector<int> int_vec{ 2, 3, 4 };
    Vector<double> double_vec{ 1.5, 2.5, 3.5 };
    Vector<int> empty_vec{};
    Vector<int> short_vec{ 1, 2 };
};
