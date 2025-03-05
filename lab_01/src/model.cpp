#include "model.hpp"
#include "errors.hpp"

#include <cstdio>
#include "QDebug"

model_t init(void)
{
    model_t model = {0};
    return model;
}

void free_model(model_t &model)
{
    if (model.edges)
        free(model.edges);

    if (model.points)
        free(model.points);
}

