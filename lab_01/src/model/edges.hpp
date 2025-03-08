#ifndef EDGES_HPP__
#define EDGES_HPP__

#include <cstdio>

// Структура для описания ребра (точка начала и конец)
typedef struct _edge_type
{
    size_t first, second;
};

using edge_t = _edge_type;

struct _edges_struct

{
    edge_t *array;
    size_t size;
};

using edges_t = _edges_struct;

edges_t edges_init(void);

#endif // EDGES_HPP__
