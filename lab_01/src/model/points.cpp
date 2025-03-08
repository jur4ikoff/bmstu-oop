#include "points.hpp"
#include "errors.hpp"
#include "point.hpp"
#include "utils.hpp"

#include <cstdlib>

points_t points_init(void)
{
    points_t new_points = { 0 };
    new_points.array = NULL;
    new_points.size = 0;

    return new_points;
}

void points_free(points_t &points)
{
    if (points.array)
        free(points.array);

    points.array = NULL;
    points.size = 0;
}

/**
 * @brief Функция читает из файла количество точек в моделе
 * @param[in, out] file Файловый дескриптор
 * @param[out] count Количество точек в моделе
 */
static err_t _read_points_count(FILE *file, size_t &count)
{
    if (file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    if ((rc = read_int_number(file, count)) == ERR_OK)
    {
        if (count < 1)
            rc = ERR_ARRAY_EMPTY;
    }

    return rc;
}

/**
 * @brief Функция читает массив точек из файла
 * @param [out] points Файлвый дескриптор
 * @param [in, out] file Файлвый дескриптор
 * @param [in] size Количество элементов массива
 */
static err_t read_points(point_t *points, FILE *file, const size_t size)
{
    err_t rc = ERR_OK;

    for (size_t i = 0; i < size; i++)
    {
        point_t new_point = { 0 };
        if ((rc = read_point(file, new_point)) == ERR_OK)
            points[i] = new_point;
        else
            break;
    }

    return rc;
}

/**
 * @brief Функция читает из файла все точки
 * @param[in, out] file - файловый дескриптер
 * @param[out] points - массив точек
 */
err_t load_points(FILE *file, points_t &points)
{
    if (file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    if ((rc = _read_points_count(file, points.size)) == ERR_OK)
    {
        points.array = (point_t *)malloc(points.size * sizeof(point_t));
        if (points.array != NULL)
        {
            rc = read_points(points.array, file, points.size);
        }
        else
            rc = ERR_MEMORY_ALLOCATION;
    }

    return rc;
}
