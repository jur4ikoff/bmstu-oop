#include "point.hpp"
#include "constants.hpp"
#include "errors.hpp"
#include "model_actions.hpp"

#include <cstdio>

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

void point_set_default_value(point_t &point)
{
    point.x = 0;
    point.y = 0;
    point.z = 0;
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

/**
 * @brief Функия реализует скейл точки
 * @param[in, out] point Точка
 * @param[in] scale Структура с масштабом
 * @param[in] center Точка центра
 */
void point_scale(point_t &point, const point_t &center, const scale_t &scale)
{
    point.x = (point.x - center.x) * scale.x + center.x;
    point.y = (point.y - center.y) * scale.y + center.y;
    point.z = (point.z - center.z) * scale.z + center.z;
}

static void rotate_x(point_t &point, const double angle)
{
    double y = point.y;
    double z = point.z;
    double cos_a = cos(angle);
    double sin_a = sin(angle);

    point.y = y * cos_a - z * sin_a;
    point.z = y * sin_a + z * cos_a;
}

// Функция для поворота точки вокруг оси Y
static void rotate_y(point_t &point, const double angle)
{
    double x = point.x;
    double z = point.z;

    double cos_a = cos(angle);
    double sin_a = sin(angle);

    point.x = x * cos_a + z * sin_a;
    point.z = -x * sin_a + z * cos_a;
}

// Функция для поворота точки вокруг оси Z
static void rotate_z(point_t &point, const double angle)
{
    double x = point.x;
    double y = point.y;

    double cos_a = cos(angle);
    double sin_a = sin(angle);

    point.x = x * cos_a - y * sin_a;
    point.y = x * sin_a + y * cos_a;
}

/**
 * @brief Функция поворачивает точку на определенный угол
 * @param[in, out] point Точка
 * @param[in] turn Структура с данными о повороте
 * @param[in] center центр
 */
void point_turn(point_t &point, const turn_t &turn)
{
    rotate_x(point, turn.x_angle);
    rotate_y(point, turn.y_angle);
    rotate_z(point, turn.z_angle);
}
