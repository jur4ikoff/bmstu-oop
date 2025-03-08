#include "point.hpp"
#include "errors.hpp"

#include <cstdio>

// Функция записывает в точку значение в точке (0, 0, 0)
void default_point(point_t &point)
{
    point.x = 0;
    point.y = 0;
    point.z = 0;
}


/**
 * @brief Функция читает из файла одну точку
 * @param[out] file ИЗМЕНЯЕМЫЙ - файловый дескриптер
 * @param[out] point ИЗМЕНЯЕМЫЙ - одна точка
 */
err_t read_point(FILE *file, point_t &point)
{
    double x, y, z;
    if ((fscanf(file, "%lf %lf %lf", &x, &y, &z)) != 3)
        return ERR_FILE_CONTENT;

    point.x = x;
    point.y = y;
    point.z = z;
    return ERR_OK;
}