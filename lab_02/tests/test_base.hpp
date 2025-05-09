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
