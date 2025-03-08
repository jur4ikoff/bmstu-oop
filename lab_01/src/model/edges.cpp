#include "edges.hpp"

#include <cstdio>

edges_t edges_init(void)
{
    edges_t new_edges = {};
    new_edges.array = NULL;
    new_edges.size = 0;

    return new_edges;
}
