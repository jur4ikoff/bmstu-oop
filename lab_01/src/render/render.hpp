#ifndef RENDER_HPP__
#define RENDER_HPP__

#include "errors.hpp"
#include "model.hpp"
#include <QPixmap>
#include <QPen>

typedef struct _render_struct_
{
    QPixmap *plane;
    QPen &draw_pen;
    QColor background_color;
} render_t;

typedef struct _line_struct
{
    point_t point_1, point_2;
} line_t;

err_t model_render(const render_t &, const model_t &);

err_t clear_scene(const render_t &render);
err_t draw_line(const render_t &, const line_t &);
err_t convert_point(point_t &, const QPixmap *);
#endif // RENDER_HPP__
