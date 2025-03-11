#include "point.hpp"
#include "constants.hpp"
#include "errors.hpp"
#include "model_actions.hpp"

#include <cstdio>

// Функция записывает в точку значение в точке (0, 0, 0)
point_t point_init(void)
{
    point_t point;

    point.x = 0;
    point.y = 0;
    point.z = 0;

    return point;
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

/**
 * @brief Функция сложения двух точек
 * @param[in] first Первая точка
 * @param[in] second Вторая точка
 * @return point_t результат сложения
 */
point_t point_add(const point_t &first, const point_t second)
{
    point_t res = point_init();

    res.x = first.x + second.x;
    res.y = first.y + second.y;
    res.z = first.z + second.z;

    return res;
}

static void rotate_x(point_t &point, const double angle)
{
    double y = point.y;
    double z = point.z;

    point.y = y * cos(angle) - z * sin(angle);
    point.z = y * sin(angle) + z * cos(angle);
}

// Функция для поворота точки вокруг оси Y
static void rotate_y(point_t &point, const double angle)
{
    double x = point.x;
    double z = point.z;
    point.x = x * cos(angle) + z * sin(angle);
    point.z = -x * sin(angle) + z * cos(angle);
}

// Функция для поворота точки вокруг оси Z
static void rotate_z(point_t &point, const double angle)
{
    double x = point.x;
    double y = point.y;
    point.x = x * cos(angle) - y * sin(angle);
    point.y = x * sin(angle) + y * cos(angle);
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
