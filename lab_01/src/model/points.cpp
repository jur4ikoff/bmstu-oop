#include "points.hpp"
#include "errors.hpp"
#include "model_actions.hpp"
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

bool points_is_empty(const points_t &points)
{
    if (points.size == 0 && points.array == NULL)
        return true;
    return false;
}

/**
 * @brief Функция читает массив точек из файла
 * @param [out] points Файлвый дескриптор
 * @param [in, out] file Файлвый дескриптор
 * @param [in] size Количество элементов массива
 */
static err_t points_read(point_t *points, FILE *file, const size_t size)
{
    if (points == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    for (size_t i = 0; i < size; i++)
    {
        point_t new_point = { 0 };
        if ((rc = read_point(new_point, file)) == ERR_OK)
            points[i] = new_point;
        else
            break;
    }

    return rc;
}

/**
 * @brief Функция читает из файла все точки
 * @param[out] points - массив точек
 * @param[in, out] file - файловый дескриптер
 */
err_t points_load(points_t &points, FILE *file)
{
    if (file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    if ((rc = read_elements_count(points.size, file)) == ERR_OK)
    {
        points.array = (point_t *)malloc(points.size * sizeof(point_t));
        if (points.array != NULL)
        {
            if ((rc = points_read(points.array, file, points.size)) != ERR_OK)
                points_free(points);
        }
        else
            rc = ERR_MEMORY_ALLOCATION;
    }

    return rc;
}

err_t points_shift(points_t &points, const shift_t &shift)
{
    err_t rc = ERR_OK;
    for (size_t i = 0; i < points.size; i++)
    {
        points.array[i].x += shift.x;
        points.array[i].y += shift.y;
        points.array[i].z += shift.z;
    }

    return rc;
}
