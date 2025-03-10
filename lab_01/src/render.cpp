#include "render.hpp"
#include "constants.hpp"
#include "edges.hpp"
#include "errors.hpp"
#include "model.hpp"
#include "point.hpp"
#include "points.hpp"

#include <QColor>
#include <QPainter>
#include <QPixmap>
#include <cstdio>

typedef struct _line_struct
{
    point_t point_1, point_2;
} line_t;

static void draw_line(QPixmap *plane, const point_t &point_1, const point_t &point_2)
{
    QPainter painter(plane);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::white, 1));

    painter.drawLine(point_1.x, point_1.y, point_2.x, point_2.y);
}

/**
 * @brief Функция проверяет, что грань существует, и записывает грань в validate_edge
 * @param[out] validate_edge Грань, прошедшая валидацию
 * @param[in] validate_edge Грань, которая будет проверятся
 * @param[in] point_count Количество точек
 */
static err_t validate_edge(edge_t &validate_edge, const edge_t &edge_to_validate, const size_t point_count)
{
    if (edge_to_validate.first >= point_count || edge_to_validate.second >= point_count)
    {
        return ERR_EDGES;
    }

    validate_edge = edge_to_validate;
    return ERR_OK;
}


/**
 * @brief Функция возвращает линию на основе массива точек и грани
 * @param[in ] render информация о размерах холста
 * @param[in] 
 */
static line_t get_line(const render_t &render, const point_t *points.array, const edge_t edge)
{
    // СДЕЛАТЬ ОТДЕЛЬНО ШТУКУ, КОТОРАЯ ДАЕТ ЛИНИЮ, И ОТДЕЛЬНО, КОТОРАЯ КОНВЕРТИРУЕТ
}

static err_t draw_edges(const render_t &render, const points_t &points, const edges_t &edges)
{
    if (render.plane == NULL || points.array == NULL || edges.array == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    line_t line = { 0 };
    edge_t edge = { 0 };
    point_t point_1 = point_init();
    point_t point_2 = point_init();

    // Рисуем линии между точками
    for (size_t i = 0; i < edges.size; i++)
    {
        if ((rc = validate_edge(edge, edges.array[i], points.size)) == ERR_OK)
        {
            size_t start_index = edge.first;
            size_t end_index = edge.second;

            //line = get_line(render, points.array, edge);
            point_1.x = render.plane->width() / 2.0 + (points.array[start_index].x);
            point_1.y = render.plane->height() / 2.0 - (points.array[start_index].y);

            point_2.x = render.plane->width() / 2.0 + (points.array[end_index].x);
            point_2.y = render.plane->height() / 2.0 - (points.array[end_index].y);
            // Рисуем линию между точками
            // rc = get_line(render.plane, line, points.array, size, edges.array[i]);
            draw_line(render.plane, point_1, point_2);
        }
        else
            break;
    }

    return rc;
}

/**
 * @brief Функция для отрисовки модели
 * @param[in] render Холст и его размеры
 * @param[in] model Данные для отрисовки
 */
err_t render_model(const render_t &render, const model_t &model)
{
    if (render.plane == NULL || model_is_empty(model))
        return ERR_ARGS;

    err_t rc = ERR_OK;
    render.plane->fill("#252525");

    rc = draw_edges(render, model.points, model.edges);
    return rc;
}
