#ifndef MODEL_HPP__
#define MODEL_HPP__

#include "errors.hpp"
#include <cstdio>

// структура для описания точки
typedef struct _point_type_
{
    double x, y, z;
} point_t;

// Структура для описания ребра (точка начала и конец)
typedef struct _edge_type
{
    size_t first, second;
} edge_t;

typedef struct _model_type_
{
    size_t points_count;
    size_t edges_count;

    point_t *points;
    edge_t *edges;
} model_t;

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

using filename_t = const char *;

model_t init(void);
void free_model(model_t &model);
err_t shift_model(model_t &model, const shift_t &shift);
err_t scale_model(model_t &model, const scale_t &scale);
err_t turn_model(model_t &model, const turn_t &turn);
err_t load_model(model_t &, const filename_t &);

#endif // MODEL_HPP__
