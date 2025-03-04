#ifndef MODEL_HPP__
#define MODEL_HPP__

#include <cstdio>
#include "errors.hpp"

// структура для описания точки
typedef struct _point_type_
{
    double x, y, z;
} point_t;

// Структура для описания ребра (точка начала и конец)
typedef struct _edge_type
{
    point_t first, second;
} edge_t;

typedef struct _model_type_
{   
    size_t points_count;
    size_t edges_count;

    point_t *points;
    edge_t *edges;
} model_t;


using filename_t = const char *;

model_t init(void);
void free_model(model_t &model);

err_t load_model(model_t &, const filename_t &);

#endif // MODEL_HPP__