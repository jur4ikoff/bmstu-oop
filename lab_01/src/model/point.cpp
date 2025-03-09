#include "point.hpp"
#include "errors.hpp"
#include "model_actions.hpp"

#include <cstdio>

// Функция записывает в точку значение в точке (0, 0, 0)
void point_default(point_t &point)
{
    point.x = 0;
    point.y = 0;
    point.z = 0;
}

/**
 * @brief Функция читает из файла одну точку
 * @param[out] point - одна точка
 * @param[in, out] file  - файловый дескриптер
 */
err_t point_read(point_t &point, FILE *file)
{
    double x, y, z;
    if ((fscanf(file, "%lf %lf %lf", &x, &y, &z)) != 3)
        return ERR_FILE_CONTENT;

    point.x = x;
    point.y = y;
    point.z = z;
    return ERR_OK;
}

/**
 * @brief Функия реализует смещение одной точки
 * @param[in, out] point Точка
 * @param[in] shift Структура со смещением
 */
void point_shift(point_t &point, const shift_t &shift)
{
    point.x += shift.x;
    point.y += shift.y;
    point.z += shift.z;
}