#ifndef EDGES_HPP__
#define EDGES_HPP__

#include "errors.hpp"

#include <cstdio>

// Структура для описания ребра (точка начала и конец)
struct _edge_type
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
void edges_free(edges_t &edges);
bool edges_is_empty(const edges_t &edges);

err_t load_edges(edges_t &edges, FILE *file);

#endif // EDGES_HPP__
