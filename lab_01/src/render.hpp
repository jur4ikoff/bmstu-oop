#ifndef RENDER_HPP__
#define RENDER_HPP__

#include "errors.hpp"
#include "model.hpp"
#include <QPixmap>

typedef struct _render_type
{
    QPixmap &plane;
    int width, height;
}render_t;

err_t render_model(const render_t &, const model_t &);
#endif // RENDER_HPP__