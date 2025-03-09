#ifndef MODEL_HPP__
#define MODEL_HPP__

#include "edges.hpp"
#include "errors.hpp"
#include "point.hpp"
#include "points.hpp"
#include "model_actions.hpp"
#include <cstdio>


struct _model_struct
{
    points_t points;
    edges_t edges;
    point_t center;
};

using model_t = _model_struct;
using filename_t = const char *;


model_t model_init(void);
void model_free(model_t &model);
err_t model_load(model_t &, const filename_t &);
err_t model_shift(model_t &model, const shift_t &shift);
err_t scale_model(model_t &model, const scale_t &scale);
err_t turn_model(model_t &model, const turn_t &turn);

#endif // MODEL_HPP__
