#include "errors.hpp"
#include "model.hpp"
#include "point.hpp"
#include "points.hpp"
#include "utils.hpp"

#include <QDebug>
#include <cstdio>
#include <stdlib.h>

/**
 * @brief Функция читает из файла одну точку
 * @param[out] file ИЗМЕНЯЕМЫЙ - файловый дескриптер
 * @param[out] edge ИЗМЕНЯЕМЫЙ - одна граница
 */
static err_t _read_edge(FILE *file, edge_t &edge)
{
    err_t rc = ERR_OK;
    size_t first, second;
    if ((rc = read_int_number(file, first)) != ERR_OK)
        return rc;
    if ((rc = read_int_number(file, second)) != ERR_OK)
        return rc;

    edge.first = first;
    edge.second = second;
    return rc;
}

/**
 * @brief Функция читает из файла все границы
 * @param[out] file ИЗМЕНЯЕМЫЙ - файловый дескриптер
 * @param[out] edges ИЗМЕНЯЕМЫЙ - массив граней
 * @param[in] points_count Количество граней в масиве
 */
static err_t _load_edges(FILE *file, edge_t **edges, size_t *edge_count)
{
    if (edges == NULL || edge_count == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    if ((rc = read_int_number(file, *edge_count)) != ERR_OK)
        return rc;

    if (*edge_count < 1)
        return ERR_ARRAY_EMPTY;

    *edges = (edge_t *)malloc(*edge_count * sizeof(edge_t));
    for (size_t i = 0; i < *edge_count; i++)
    {
        edge_t new_edge = { 0 };
        if ((rc = _read_edge(file, new_edge)) != ERR_OK)
            return rc;

        (*edges)[i] = new_edge;
    }

    return rc;
}

/**
 * @brief Функция считывает данные из файла и записывает их в temp_model
 * @param[out] file ИЗМЕНЯЕМЫЙ Файловый дескриптер
 * @param[out] temp_model ссылка на структуры для записи. Изменяемый параметр
 */
static err_t _load_model(FILE *file, model_t &temp_model)
{
    if (file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    points_t points;
    size_t points_count = 0;
    if ((rc = load_points(file, points)) != ERR_OK)
    {
        points_free(points);
    }
    else
    {
        temp_model.points = points;

        edge_t *edges = NULL;
        size_t edges_count = 0;
        if ((rc = _load_edges(file, &edges, &edges_count)) != ERR_OK)
        {
            points_free(points);
            free(edges);
        }
        else
        {
            temp_model.edges.array = edges;
            temp_model.edges.size = edges_count;
        }
    }

    return rc;
}

/**
 * @brief Функция загружает данные из файла в структуру типа model_t
 * @param[out] model Объект типа model_t для записи данных из файла, изменяемый параметр
 * @param[in] filename Имя файла для чтения
 */
err_t load_model(model_t &model, const filename_t &filename)
{
    err_t rc = ERR_OK;

    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        // Инициализируем временную модель
        model_t temp_model = init();
        rc = _load_model(file, temp_model);
        fclose(file);

        if (rc == ERR_OK)
        {
            free_model(model);
            model = temp_model;
        }
    }
    else
    {
        rc = ERR_FILE;
    }
    return rc;
}
