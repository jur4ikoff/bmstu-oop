#ifndef RENDER_HPP__
#define RENDER_HPP__

#include "errors.hpp"
#include "model.hpp"
#include <QPixmap>
#include <QPen>

typedef struct _render_struct_
{
    QPixmap &plane;
    QPen &draw_pen;
    QColor background_color;
} render_t;

typedef struct _line_struct
{
    point_t point_1, point_2;
} line_t;

err_t model_render(const render_t &, const model_t &);

void plane_clear(const render_t &);


err_t draw_line(const render_t &, const line_t &);

#endif // RENDER_HPP__
