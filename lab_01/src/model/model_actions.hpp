#ifndef MODEL_ACTIONS_HPP__
#define MODEL_ACTIONS_HPP__

struct _shift_struct
{
    double x, y, z;
};

struct _scale_struct
{
    double x, y, z;
};

struct _turn_struct
{
    double x_angle, y_angle, z_angle;
};

using shift_t = _shift_struct;
using scale_t = _scale_struct;
using turn_t = _turn_struct;
#endif
