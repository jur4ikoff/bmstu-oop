#ifndef EDGES_HPP__
#define EDGES_HPP__

#include "errors.hpp"

#include <cstdio>

// Структура для описания ребра (точка начала и конец)
typedef struct _edge_type
{
    size_t first, second;
} edge_t;

typedef struct _edges_struct
{
    edge_t *array;
    size_t size;
} edges_t;

void edges_init(edges_t &new_edges);
void edges_free(edges_t &edges);
bool edges_is_empty(const edges_t &edges);

err_t edges_validate(const edges_t &, const size_t);
err_t edges_load(edges_t &edges, FILE *file);

#endif // EDGES_HPP__
