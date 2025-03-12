#include "render.hpp"
#include "errors.hpp"
#include "model.hpp"
#include "point.hpp"

#include <QPainter>
#include <QPixmap>
#include <cstdio>

static void draw_line_by_points(QPainter &painter, const point_t &point_1, const point_t &point_2)
{
    painter.drawLine(point_1.x, point_1.y, point_2.x, point_2.y);
}

/**
 * @brief Функция рисует одну линию, состоящую из двух точек
 * @param[in] render Структура с данными для рисования
 * @param[in] point_1 Точка 1
 * @param[in] point_2 Точка 2
 */
err_t draw_line(const render_t &render, const line_t &line)
{
    QPixmap *plane = &render.plane;
    QPainter painter(plane);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(render.draw_pen);

    draw_line_by_points(painter, line.point_1, line.point_2);
    return ERR_OK;
}

void plane_fill(QPixmap &plane, const QColor &color)
{
    plane.fill(color);
}

void plane_clear(const render_t &render)
{
    plane_fill(render.plane, render.background_color);
}

/**
 * @brief Конвертация координат в формат, необходимый для вывода на экран
 * @param[in, out] point Точка 2
 * @param[in] plane Данные о холсте
 */
void convert_point(point_t &point, const QPixmap &plane)
{
    point.x = plane.width() / 2.0 + point.x;
    point.y = plane.height() / 2.0 - point.y;
}
