#include "point.hpp"
#include "constants.hpp"
#include "errors.hpp"
#include "model_actions.hpp"

#include <cstdio>

static double to_radians(const double &angle)
{
    return angle * (PI / 180);
}

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
void point_scale(point_t &point, const scale_t &scale, const point_t &center)
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

static void rotate_x(point_t &point, const point_t &center, const double angle)
{
    double rad_angle = to_radians(angle);
    double y = point.y - center.y;
    double z = point.z - center.z;

    point.y = center.y + y * cos(rad_angle) - z * sin(rad_angle);
    point.z = center.z + y * sin(rad_angle) + z * cos(rad_angle);
}

// Функция для поворота точки вокруг оси Y
static void rotate_y(point_t &point, const point_t &center, const double angle)
{
    double rad_angle = to_radians(angle);

    double x = point.x - center.x;
    double z = point.z - center.z;
    point.x = center.x + x * cos(rad_angle) + z * sin(rad_angle);
    point.z = center.z - x * sin(rad_angle) + z * cos(rad_angle);
}

// Функция для поворота точки вокруг оси Z
static void rotate_z(point_t &point, const point_t &center, const double angle)
{
    double rad_angle = to_radians(angle);

    double x = point.x - center.x;
    double y = point.y - center.y;
    point.x = center.x + x * cos(rad_angle) - y * sin(rad_angle);
    point.y = center.y + x * sin(rad_angle) + y * cos(rad_angle);
}


/**
 * @brief Функция поворачивает точку на определенный угол
 * @param[in, out] point Точка
 * @param[in] turn Структура с данными о повороте
 * @param[in] center центр
 */
void point_turn(point_t &point, const turn_t &turn, const point_t &center)
{
    rotate_x(point, center, turn.x_angle);
    rotate_y(point, center, turn.y_angle);
    rotate_z(point, center, turn.z_angle);
}
