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

/**
 * @brief Функция возвращает линию на основе массива точек и грани
 * @param[out] line линия
 * @param[in] points массив точек
 * @param[in] edge структура с данными о грани
 * @return Код возврата
 */
static err_t get_line(line_t &line, const point_t *points, const edge_t &edge)
{
    if (points == NULL)
        return ERR_ARGS;

    size_t first = edge.first;
    size_t second = edge.second;

    line = {points[first], points[second]};
    return ERR_OK;
}

/**
 * @brief Конвертация координат в формат, необходимый для вывода на экран
 * @param[in, out] line Структура с линией
 * @param[in] render структура с данными для рисования
 */
static err_t convert_line(line_t &line, const render_t &render)
{
    if (render.plane == NULL)
        return ERR_ARGS;

    err_t rc = convert_point(line.point_1, render.plane);
    if (rc == ERR_OK)
    {
        rc = convert_point(line.point_2, render.plane);
    }

    return rc;
}

/**
 * @brief Функцмя рисует одну грань
 * @param[in] render Структура с данными для вывода
 * @param[in] points Массив точек
 * @param[in] edge одна грань
 */
static err_t draw_edge(const render_t &render, const point_t *points, const edge_t &edge)
{
    if (points == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    line_t line;
    if ((rc = get_line(line, points, edge)) == ERR_OK)
    {
        if ((rc = convert_line(line, render)) == ERR_OK)
        {
            rc = draw_line(render, line);
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

    err_t rc = model_validate(model);
    if (rc == ERR_OK)
    {
        rc = clear_scene(render);
        if (rc == ERR_OK)
        {
            rc = draw_model(render, model);
        }
    }
    return rc;
}
