#ifndef MODEL_HPP__
#define MODEL_HPP__

#include "errors.hpp"
#include "point.hpp"
#include "edges.hpp"
#include "points.hpp"
#include <cstdio>

struct _model_struct
{
    points_t points;
    edges_t edges;
    point_t center;
};

typedef struct
{
    double x, y, z;
} shift_t;

typedef struct
{
    double x, y, z;
} scale_t;

typedef struct
{
    double x_angle, y_angle, z_angle;
} turn_t;

using model_t = _model_struct;
using filename_t = const char *;

model_t init(void);
void free_model(model_t &model);
err_t shift_model(model_t &model, const shift_t &shift);
err_t scale_model(model_t &model, const scale_t &scale);
err_t turn_model(model_t &model, const turn_t &turn);
err_t load_model(model_t &, const filename_t &);

#endif // MODEL_HPP__
