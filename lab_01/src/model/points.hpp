#ifndef POINTS_HPP__
#define POINTS_HPP__

#include "point.hpp"

#include <cstdio>

struct _points_struct
{
    point_t *array;
    size_t size;
};

using points_t = _points_struct;

#endif // POINTS_HPP__
