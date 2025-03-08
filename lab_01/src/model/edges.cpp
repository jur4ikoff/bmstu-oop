#include "edges.hpp"

#include <cstdio>
#include <cstdlib>

edges_t edges_init(void)
{
    edges_t new_edges = {};
    new_edges.array = NULL;
    new_edges.size = 0;

    return new_edges;
}

void edges_free(edges_t &edges)
{
    if (edges.array)
        free(edges.array);

    edges.array = NULL;
    edges.size = 0;
}