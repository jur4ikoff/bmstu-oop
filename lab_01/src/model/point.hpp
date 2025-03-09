#ifndef POINT_HPP__
#define POINT_HPP__

#include "errors.hpp"
#include "model_actions.hpp"

// Структура для описания точки
struct _point_struct
{
    double x, y, z;
};

using point_t = _point_struct;

point_t point_init(void);
point_t point_add(const point_t &, const point_t);

err_t point_read(point_t &, FILE *);

void point_shift(point_t &, const shift_t &);
void point_scale(point_t &point, const scale_t &scale, const point_t &center);

#endif // POINTS_HPP__
