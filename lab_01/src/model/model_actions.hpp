#ifndef MODEL_ACTIONS_HPP__
#define MODEL_ACTIONS_HPP__

typedef struct _shift_struct
{
    double x, y, z;
} shift_t;

typedef struct _scale_struct
{
    double x, y, z;
} scale_t;

// Углы заданы в радианах
typedef struct _turn_struct
{
    double x_angle, y_angle, z_angle;
} turn_t;

#endif
