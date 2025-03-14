#ifndef RENDER_MODEL_HPP__
#define RENDER_MODEL_HPP__

#include "render.hpp"
#include "render_model_qt6.hpp"

#include "errors.hpp"
#include "model.hpp"
#include "point.hpp"

#include <QPainter>
#include <QPixmap>
#include <cstdio>

void plane_fill(QPixmap &plane, const QColor &color);
void convert_point(point_t &, const QPixmap &);
void convert_line(line_t &line, const render_t &render);

#endif // RENDER_MODEL_HPP__