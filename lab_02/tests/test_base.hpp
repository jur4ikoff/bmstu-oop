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

class BaseVectors
{
protected:
    Vector<int> int_vec{2, 3, 4};
    Vector<double> double_vec{1.5, 2.5, 3.5};
    Vector<int> empty_vec{};
    Vector<int> short_vec{1, 2};
};
