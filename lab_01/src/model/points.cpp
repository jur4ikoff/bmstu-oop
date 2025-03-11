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
 */
static err_t points_read(points_t &points, FILE *file)
{
    if (points.array == NULL || file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && (i < points.size); i++)
    {
        rc = point_read(points.array[i], file);
    }
    return rc;
}

/**
 * @brief Функция выделяет память под массив точек
 * @param[out] points - Структура точек
 * @param[in] size - Количество элементов в массиве точек
 */
static err_t points_allocate(points_t &points, const size_t size)
{
    if (size == 0)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    points.size = size;
    points.array = (point_t *)malloc(points.size * sizeof(point_t));

    if (points.array == NULL)
        rc = ERR_MEMORY_ALLOCATION;

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
    size_t count;
    if ((rc = read_elements_count(count, file)) == ERR_OK)
    {
        rc = points_allocate(points, count);
        if (rc == ERR_OK)
        {
            rc = points_read(points, file);
            if (rc != ERR_OK)
                points_free(points);
        }
    }

    return rc;
}

/**
 * @brief Функия реализует смещение всех точек
 * @param[in, out] points структура точек
 * @param[in] shift Структура со смещением
 */
err_t points_shift(points_t &points, const shift_t &shift)
{
    if (points.array == NULL)
        return ERR_ARGS;

    for (size_t i = 0; i < points.size; i++)
    {
        point_shift(points.array[i], shift);
    }

    return ERR_OK;
}

/**
 * @brief Функия реализует скейл всех точек
 * @param[in, out] points структура точек
 * @param[in] shift Структура со смещением
 * @param[in] center Центр
 */
err_t points_scale(points_t &points, const scale_t &scale, const point_t &center)
{
    if (points.array == NULL)
        return ERR_ARGS;

    for (size_t i = 0; i < points.size; i++)
    {
        point_scale(points.array[i], scale, center);
    }

    return ERR_OK;
}

/**
 * @brief Функция определяет центр фигуры
 * @param[out] center Точка - центр
 * @param[in] points Структура типа points_t
 */
err_t points_calculate_center(point_t &center, const points_t &points)
{
    if (points.size == 0 || points.array == NULL)
    {
        return ERR_EMPTY_MODEL;
    }

    for (size_t i = 0; i < points.size; ++i)
    {
        center = point_add(center, points.array[i]);
    }

    center.x /= points.size;
    center.y /= points.size;
    center.z /= points.size;
    return ERR_OK;
}

/**
 * @brief Функция поворачивает массив точек на определенный угол
 * @param[in, out] points Массив точек
 * @param[in] turn Структура с данными о повороте
 * @param[in] center точка с центром
 */
err_t points_turn(points_t &points, const turn_t &turn)
{
    if (points.array == NULL || points.size == 0)
        return ERR_ARGS;

    for (size_t i = 0; i < points.size; i++)
    {
        point_turn(points.array[i], turn);
    }

    return ERR_OK;
}
