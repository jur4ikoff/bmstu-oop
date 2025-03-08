#include "points.hpp"
#include "point.hpp"
#include <cstdlib>

points_t points_init(void)
{
    points_t new_points = { 0 };
    new_points.array = NULL;
    new_points.size = 0;

    return new_points;
}

void points_free(points_t &points)
{
    if (points.array)
        free(points.array);

    points.array = NULL;
    points.size = 0;
}
