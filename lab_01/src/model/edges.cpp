#include "edges.hpp"
#include "errors.hpp"
#include "utils.hpp"

#include <cstdio>
#include <cstdlib>

edges_t edges_init(void)
{
    edges_t new_edges = {};
    new_edges.array = NULL;
    new_edges.size = 0;

    return new_edges;
}

void edges_free(edges_t &edges)
{
    if (edges.array)
        free(edges.array);

    edges.array = NULL;
    edges.size = 0;
}

bool edges_is_empty(const edges_t &edges)
{
    if (edges.size == 0 && edges.array == NULL)
        return true;
    return false;
}

/**
 * @brief Функция читает из файла одну точку
 * @param[out] edge - одна грань
 * @param[in, out] file - файловый дескриптор
 */
static err_t read_edge(edge_t &edge, FILE *file)
{
    err_t rc = ERR_OK;
    size_t first, second;
    if ((rc = read_int_number(first, file)) != ERR_OK)
        return rc;
    if ((rc = read_int_number(second, file)) != ERR_OK)
        return rc;

    edge.first = first;
    edge.second = second;
    return rc;
}

/**
 * @brief Функция читает все грани из файла
 * @param[out] edges Массив граней
 * @param[in, out] file Файловый дескриптор
 * @param[in] size Размер массива
 */
static err_t read_edges(edge_t *edges, FILE *file, const size_t size)
{
    if (edges == NULL || file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && (i < size); i++)
    {
        rc = read_edge(edges[i], file);
    }
    return rc;
}

/**
 * @brief Функция читает из файла все границы
 * @param[out] edges - Структура для записей информации о гранях
 * @param[in, out] file  - файловый дескриптор
 */
err_t load_edges(edges_t &edges, FILE *file)
{
    if (file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    if ((rc = read_elements_count(edges.size, file)) == ERR_OK)
    {
        edges.array = (edge_t *)malloc(edges.size * sizeof(edge_t));
        if (edges.array != NULL)
        {
            if ((rc = read_edges(edges.array, file, edges.size)) != ERR_OK)
                free(edges.array);
        }
        else
            rc = ERR_MEMORY_ALLOCATION;
    }

    return rc;
}

/**
 * @brief Функция проверяет, что все ребра существуют
 * @param[in] edge Одна грань
 * @param[in] points_count Количество точек в моделе
 */
static err_t edge_validate(const edge_t edge, const size_t points_count)
{
    if (edge.first >= points_count || edge.second >= points_count)
        return ERR_EDGES;

    return ERR_OK;
}

/**
 * @brief Функция проверяет, что все ребра существуют
 * @param[in] edges Структура, хранящая грани
 * @param[in] points_count Количество точек в моделе
 */
err_t edges_validate(const edges_t edges, const size_t points_count)
{
    err_t rc = ERR_OK;
    if (edges.size > 0)
    {
        for (size_t i = 0; rc == ERR_OK && (i < edges.size); i++)
        {
            rc = edge_validate(edges.array[i], points_count);
        }
    }
    else
        rc = ERR_EDGES;

    return rc;
}
