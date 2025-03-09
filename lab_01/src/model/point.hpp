#ifndef POINT_HPP__
#define POINT_HPP__

#include "errors.hpp"

// Структура для описания точки
struct _point_struct
{
    double x, y, z;
};

using point_t = _point_struct;

void default_point(point_t &);
err_t read_point(point_t &, FILE *);

#endif // POINTS_HPP__
