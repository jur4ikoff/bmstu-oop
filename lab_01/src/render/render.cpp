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
 * @param[in] render структура с данными для рисования
 */
static err_t convert_line(point_t &point_1, point_t &point_2, const render_t &render)
{
    if (render.plane == NULL)
        return ERR_ARGS;

    point_1.x = render.plane->width() / 2.0 + point_1.x;
    point_1.y = render.plane->height() / 2.0 - point_1.y;

    point_2.x = render.plane->width() / 2.0 + point_2.x;
    point_2.y = render.plane->height() / 2.0 - point_2.y;

    return ERR_OK;
}

/**
 * @brief Функцмя рисует одну грань
 * @param[in, out] plane Указатель на холст для рисование
 * @param[in] points Массив точек
 * @param[in] edge одна грань
 */
static err_t draw_edge(const render_t &render, const point_t *points, const edge_t &edge)
{
    if (points == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    line_t line = {};
    if ((rc = get_line(line, points, edge)) == ERR_OK)
    {
        if ((rc = convert_line(line.point_1, line.point_2, render)) == ERR_OK)
        {
            rc = draw_line(render, line.point_1, line.point_2);
        }
    }

    return rc;
}

/**
 * @brief Функция рисует все грани фигуры
 * @param[in] render Структура с данными о холсте
 * @param[in] edges Структура с данными о гранях фигуры
 * @param[in] points Структурами с данными о вершине фигуры
 * @return Код возврата
 */
static err_t draw_edges(const render_t &render, const edges_t &edges, const points_t &points)
{
    if (points.array == NULL || edges.array == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && (i < edges.size); i++)
    {
        rc = draw_edge(render, points.array, edges.array[i]);
    }

    return rc;
}

static err_t draw_model(const render_t &render, const model_t &model)
{
    return draw_edges(render, model.edges, model.points);
}

/**
 * @brief Функция для отрисовки модели
 * @param[in] render Холст и его размеры
 * @param[in] model Данные для отрисовки
 */
err_t model_render(const render_t &render, const model_t &model)
{
    if (model_is_empty(model))
        return ERR_EMPTY_MODEL;

    err_t rc = clear_scene(render);
    if (rc == ERR_OK)
    {
        rc = model_validate(model);
        if (rc == ERR_OK)
        {
            rc = draw_model(render, model);
        }
    }
    return rc;
}
