#ifndef POINTS_HPP__
#define POINTS_HPP__

#include "errors.hpp"
#include "model_actions.hpp"
#include "point.hpp"

#include <cstdio>

typedef struct _points_struct
{
    point_t *array;
    size_t size;
} points_t;

points_t points_init(void);
void points_free(points_t &);
bool points_is_empty(const points_t &);

err_t points_calculate_center(point_t &, const points_t &);
err_t points_load(points_t &, FILE *);
err_t points_shift(points_t &, const shift_t &);
err_t points_scale(points_t &, const scale_t &, const point_t &);
err_t points_turn(points_t &, const turn_t &);

#endif // POINTS_HPP__
