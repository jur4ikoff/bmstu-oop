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
    if (file == NULL)
        return ERR_FILE;

    err_t rc = ERR_OK;
    if ((fscanf(file, "%lf %lf %lf", &point.x, &point.y, &point.z)) != 3)
        rc = ERR_FILE_CONTENT;

    return rc;
}

void point_add(point_t &point_1, const point_t &point_2)
{
    point_1.x += point_2.x;
    point_1.y += point_2.y;
    point_1.z += point_2.z;
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
void point_scale(point_t &point, const scale_t &scale)
{
    point.x *= scale.x;
    point.y *= scale.y;
    point.z *= scale.z;
}

static void rotate_x(point_t &point, const trig_funcs_t &func)
{
    double y = point.y;
    double z = point.z;
    double r_cos = func.r_cos;
    double r_sin = func.r_sin;

    point.y = y * r_cos - z * r_sin;
    point.z = y * r_sin + z * r_cos;
}

// Функция для поворота точки вокруг оси Y
static void rotate_y(point_t &point, const trig_funcs_t &func)
{
    double x = point.x;
    double z = point.z;

    double r_cos = func.r_cos;
    double r_sin = func.r_sin;

    point.x = x * r_cos + z * r_sin;
    point.z = -x * r_sin + z * r_cos;
}

// Функция для поворота точки вокруг оси Z
static void rotate_z(point_t &point, const trig_funcs_t &func)
{
    double x = point.x;
    double y = point.y;

    double r_cos = func.r_cos;
    double r_sin = func.r_sin;

    point.x = x * r_cos - y * r_sin;
    point.y = x * r_sin + y * r_cos;
}

/**
 * @brief Функция поворачивает точку на определенный угол
 * @param[in, out] point Точка
 * @param[in] turn Структура с данными о повороте
 * @param[in] center центр
 */
void point_turn(point_t &point, const trig_val_t &trig)
{
    rotate_x(point, trig.x_angle);
    rotate_y(point, trig.y_angle);
    rotate_z(point, trig.z_angle);
}
