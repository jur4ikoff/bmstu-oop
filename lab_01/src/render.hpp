#ifndef RENDER_HPP__
#define RENDER_HPP__

#include "errors.hpp"
#include "model.hpp"
#include <QPixmap>

typedef struct _render_struct_
{
    QPixmap *plane;
} render_t;

err_t render_model(const render_t &, const model_t &);
#endif // RENDER_HPP__
