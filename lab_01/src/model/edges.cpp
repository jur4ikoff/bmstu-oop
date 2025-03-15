#include "edges.hpp"
#include "errors.hpp"
#include "utils.hpp"

#include <cstdio>
#include <cstdlib>

void edges_init(edges_t &new_edges)
{
    new_edges.array = NULL;
    new_edges.size = 0;
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
    if (file == NULL)
        return ERR_FILE;

    err_t rc = ERR_OK;
    if ((fscanf(file, "%zu %zu", &edge.first, &edge.second)) != 2)
        rc = ERR_FILE_CONTENT;

    return rc;
}

/**
 * @brief Функция читает все грани из файла
 * @param[out] edges Структура граней
 * @param[in, out] file Файловый дескриптор
 */
static err_t edges_read(edge_t *array, FILE *file, const size_t size)
{
    if (array == NULL || file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && (i < size); i++)
    {
        rc = edge_read(array[i], file);
    }
    return rc;
}

/**
 * @brief Функция выделяет память под массив граней
 * @param[out] edges Структура граней
 * @param[in] size Количество элементов в массиве граней
 */
static err_t edges_allocate(edge_t **array, const size_t size)
{
    if (size == 0)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    *array = (edge_t *)malloc(size * sizeof(edges_t));

    if (*array == NULL)
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
    if ((rc = read_elements_count(edges.size, file)) == ERR_OK)
    {
        rc = edges_allocate(&edges.array, edges.size);
        if (rc == ERR_OK)
        {
            rc = edges_read(edges.array, file, edges.size);
            if (rc != ERR_OK)
                free(edges.array);
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
    err_t rc = ERR_OK;
    if (edge.first >= points_count || edge.second >= points_count)
        rc = ERR_EDGES;

    return rc;
}

/**
 * @brief Функция проверяет, что все ребра существуют
 * @param[in] edges Структура граней
 * @param[in] edges_count Количество граней в моделе
 */
err_t edges_validate(const edges_t &edges, const size_t points_count)
{
    if (edges.size < 1 || edges.array == NULL || points_count < 1)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && (i < edges.size); i++)
    {
        rc = edge_validate(edges.array[i], points_count);
    }

    return rc;
}
