#ifndef MODEL_HPP__
#define MODEL_HPP__

#include "edges.hpp"
#include "errors.hpp"
#include "point.hpp"
#include "points.hpp"
#include "model_actions.hpp"
#include <cstdio>


typedef struct _model_struct
{
    points_t points;
    edges_t edges;
    point_t center;
} model_t;


using filename_t = const char *;


model_t model_init(void);
void model_free(model_t &);
bool model_is_empty(const model_t &model);

err_t model_load(model_t &, const filename_t &);
err_t model_shift(model_t &, const shift_t &);
err_t model_scale(model_t &, const scale_t &);
err_t model_turn(model_t &, const turn_t &);
err_t model_validate(const edges_t &edges, const points_t &points);

#endif // MODEL_HPP__
