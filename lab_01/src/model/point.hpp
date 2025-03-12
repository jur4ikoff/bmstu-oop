#ifndef POINT_HPP__
#define POINT_HPP__

#include "errors.hpp"
#include "model_actions.hpp"

// Структура для описания точки
typedef struct _point_struct
{
    double x, y, z;
} point_t;

typedef struct
{
    double r_cos, r_sin;
} trig_funcs_t;

typedef struct
{
    trig_funcs_t x_angle;
    trig_funcs_t y_angle;
    trig_funcs_t z_angle;

} trig_val_t;

err_t point_read(point_t &, FILE *);

void point_set_default_value(point_t &);
void point_shift(point_t &, const shift_t &);
void point_scale(point_t &, const scale_t &);
void point_turn(point_t &, const trig_val_t &);
void point_add(point_t &, const point_t &);
#endif // POINTS_HPP__
