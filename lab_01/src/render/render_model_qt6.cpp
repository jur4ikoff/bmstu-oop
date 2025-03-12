#include "render.hpp"
#include "errors.hpp"
#include "model.hpp"
#include "point.hpp"

#include <QPainter>
#include <QPixmap>
#include <cstdio>

/**
 * @brief Функция рисует одну линию, состоящую из двух точек
 * @param[in] render Структура с данными для рисования
 * @param[in] point_1 Точка 1
 * @param[in] point_2 Точка 2
 */
err_t draw_line(const render_t &render, const point_t &point_1, const point_t &point_2)
{
    if (render.plane == NULL)
        return ERR_ARGS;

    QPainter painter(render.plane);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(render.draw_pen);

    painter.drawLine(point_1.x, point_1.y, point_2.x, point_2.y);
    return ERR_OK;
}

err_t clear_scene(const render_t &render)
{
    if (render.plane == NULL)
        return ERR_ARGS;

    render.plane->fill(render.background_color);
    return ERR_OK;
}