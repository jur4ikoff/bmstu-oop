#include "render.hpp"
#include "constants.hpp"
#include "edges.hpp"
#include "render_model_qt6.hpp"
#include "errors.hpp"
#include "model.hpp"
#include "point.hpp"
#include "points.hpp"

#include <QColor>
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
        convert_line(line, render);
        rc = draw_line(render, line);
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
    if (points.array == NULL || edges.array == NULL || edges.size == 0 || points.size == 0)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && (i < edges.size); i++)
    {
        rc = draw_edge(render, points.array, edges.array[i]);
    }

    return rc;
}

/**
 * @brief Функция для отрисовки модели
 * @param[in] render Холст и его размеры
 * @param[in] model Данные для отрисовки
 */
err_t model_render(const render_t &render, const model_t &model)
{
    err_t rc = ERR_OK;
    if (edges_is_empty(model.edges) || points_is_empty(model.points))
    {
        rc = ERR_EMPTY_MODEL;
    }
    else
    {
        plane_clear(render);
        err_t rc = draw_edges(render, model.edges, model.points);
    }

    return rc;
}
