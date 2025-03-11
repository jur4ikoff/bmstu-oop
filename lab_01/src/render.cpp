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

/**
 * @brief Функция рисует одну линию, состоящую из двух точек
 * @param[in, out] plane Холст для рисования
 * @param[in] point_1 Точка 1
 * @param[in] point_2 Точка 2
 */
static err_t draw_line(QPixmap *plane, const point_t &point_1, const point_t &point_2)
{
    if (plane == NULL)
        return ERR_ARGS;

    QPainter painter(plane);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::white, 1));

    painter.drawLine(point_1.x, point_1.y, point_2.x, point_2.y);
    return ERR_OK;
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
 * @param[out] line линия
 * @param[in] points массив точек
 * @param[in] edge структура с данными о грани
 * @return Код возврата
 */
static err_t get_line(line_t &line, const point_t *points, const edge_t edge)
{
    if (points == NULL)
        return ERR_ARGS;
    point_t point_1 = point_init();
    point_t point_2 = point_init();

    size_t first = edge.first;
    size_t second = edge.second;

    point_1.x = points[first].x;
    point_1.y = points[first].y;

    point_2.x = points[second].x;
    point_2.y = points[second].y;

    line.point_1 = point_1;
    line.point_2 = point_2;
    return ERR_OK;
}

/**
 * @brief Конвертация координат в формат, необходимый для вывода на экран
 * @param[in, out] point_1 Точка 1
 * @param[in, out] point_2 Точка 2
 * @param[in] plane Холст для рисования
 */
static err_t convert_line(point_t &point_1, point_t &point_2, const QPixmap *plane)
{
    if (plane == NULL)
        return ERR_ARGS;

    point_1.x = plane->width() / 2.0 + point_1.x;
    point_1.y = plane->height() / 2.0 - point_1.y;

    point_2.x = plane->width() / 2.0 + point_2.x;
    point_2.y = plane->height() / 2.0 - point_2.y;

    return ERR_OK;
}

/**
 * @brief Функцмя рисует одну грань
 * @param[in, out] plane Указатель на холст для рисование
 * @param[in] points Массив точек
 * @param[in] edge одна грань
 */
static err_t draw_edge(QPixmap *plane, const point_t *points, const edge_t &edge)
{
    if (plane == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    line_t line = {};
    if ((rc = get_line(line, points, edge)) == ERR_OK)
    {
        if ((rc = convert_line(line.point_1, line.point_2, plane)) == ERR_OK)
        {
            rc = draw_line(plane, line.point_1, line.point_2);
        }
    }

    return rc;
}

/**
 * @brief Функция рисует все грани фигуры
 * @param[in] render Структура с данными о холсте
 * @param[in] points Структурами с данными о вершине фигуры
 * @param[in] edges Структура с данными о гранях фигуры
 * @return Код возврата
 */
static err_t draw_edges(const render_t &render, const points_t &points, const edges_t &edges)
{
    if (render.plane == NULL || points.array == NULL || edges.array == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    edge_t edge;
    for (size_t i = 0; rc == ERR_OK && (i < edges.size); i++)
    {
        if ((rc = validate_edge(edge, edges.array[i], points.size)) == ERR_OK)
        {
            rc = draw_edge(render.plane, points.array, edge);
        }
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
    if ((rc = model_validate(model)) == ERR_OK)
    {
        render.plane->fill("#252525");
        rc = draw_edges(render, model.points, model.edges);
    }
    return rc;
}
