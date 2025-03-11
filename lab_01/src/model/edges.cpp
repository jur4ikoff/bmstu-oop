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
static err_t edge_read(edge_t &edge, FILE *file)
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
static err_t edges_read(edge_t *edges, FILE *file, const size_t size)
{
    if (edges == NULL || file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && (i < size); i++)
    {
        rc = edge_read(edges[i], file);
    }
    return rc;
}

/**
 * @brief Функция выделяет память под массив граней
 * @param[out] edges Структура граней
 * @param[in] size Количество элементов в массиве граней
 */
static err_t edges_allocate(edges_t &edges, const size_t size)
{
    if (size == 0)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    edges.size = size;
    edges.array = (edge_t *)malloc(edges.size * sizeof(edges_t));

    if (edges.array == NULL)
        rc = ERR_MEMORY_ALLOCATION;

    return rc;
}

/**
 * @brief Функция читает из файла все границы
 * @param[out] edges Структура для записей информации о гранях
 * @param[in, out] file файловый дескриптор
 */
err_t edges_load(edges_t &edges, FILE *file)
{
    if (file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    size_t count;
    if ((rc = read_elements_count(count, file)) == ERR_OK)
    {
        rc = edges_allocate(edges, count);
        if (rc == ERR_OK)
        {
            rc = edges_read(edges.array, file, edges.size);
            if (rc != ERR_OK)
                edges_free(edges);
        }
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
 * @param[in] edges массив граней
 * @param[in] edges_count Количество граней в моделе
 * @param[in] points_count Количество точек в моделе
 */
err_t edges_validate(const edge_t *edges, const size_t edges_count, const size_t points_count)
{
    if (edges_count < 1 || points_count < 1 || edges == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && (i < edges_count); i++)
    {
        rc = edge_validate(edges[i], points_count);
    }

    return rc;
}
