#include "points.hpp"
#include "errors.hpp"
#include "model_actions.hpp"
#include "point.hpp"
#include "utils.hpp"

#include <cstdlib>

void points_init(points_t &new_points)
{
    new_points.array = NULL;
    new_points.size = 0;
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
static err_t points_read(point_t *array, FILE *file, const size_t size)
{
    if (array == NULL || file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    for (size_t i = 0; rc == ERR_OK && (i < size); i++)
    {
        rc = point_read(array[i], file);
    }
    return rc;
}

/**
 * @brief Функция выделяет память под массив точек
 * @param[out] points Структура точек
 * @param[in] size Количество элементов в массиве точек
 */
static err_t points_allocate(point_t **array, const size_t size)
{
    if (size == 0)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    *array = (point_t *)malloc(size * sizeof(point_t));

    if (*array == NULL)
        rc = ERR_MEMORY_ALLOCATION;

    return rc;
}

/**
 * @brief Функция читает из файла все точки
 * @param[out] points массив точек
 * @param[in, out] file файловый дескриптер
 */
err_t points_load(points_t &points, FILE *file)
{
    if (file == NULL)
        return ERR_ARGS;

    err_t rc = read_elements_count(points.size, file);
    if (rc == ERR_OK)
    {
        rc = points_allocate(&points.array, points.size);
        if (rc == ERR_OK)
        {
            rc = points_read(points.array, file, points.size);
            if (rc != ERR_OK)
                free(points.array);
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
    if (points.array == NULL || points.size == 0)
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
 * @param[in] center Центр
 * @param[in] shift Структура со смещением
 */
err_t points_scale(points_t &points, const scale_t &scale)
{
    if (points.array == NULL)
        return ERR_ARGS;

    for (size_t i = 0; i < points.size; i++)
    {
        point_scale(points.array[i], scale);
    }

    return ERR_OK;
}

/**
 * @brief Функция считает сумму всех точекя
 * @param[out] sum Точка сумма всех остальных
 * @param[in] points Массив точек
 * @param[in] size Размер массива
 */
static err_t sum_all_points(point_t &sum, const point_t *points, const size_t size)
{
    if (points == NULL || size == 0)
        return ERR_ARGS;

    for (size_t i = 0; i < size; i++)
    {
        point_add(sum, points[i]);
    }

    return ERR_OK;
}

static void div_point_on_koef(point_t &point, double koef)
{
    point.x /= koef;
    point.y /= koef;
    point.z /= koef;
}

/**
 * @brief Функция определяет центр фигуры
 * @param[out] center Точка - центр
 * @param[in] points Точки
 */
err_t points_calculate_center(point_t &center, const points_t &points)
{
    if (points.size == 0 || points.array == NULL)
        return ERR_EMPTY_MODEL;

    point_set_default_value(center);
    err_t rc = sum_all_points(center, points.array, points.size);
    if (rc == ERR_OK)
    {
        div_point_on_koef(center, points.size);
    }

    return ERR_OK;
}

static void get_trig_functions(trig_funcs_t &trig_functions, const double angle)
{
    trig_functions.r_cos = cos(angle);
    trig_functions.r_sin = sin(angle);
}

static void convert_angle_to_triangle(trig_val_t &trig, const turn_t &turn)
{
    get_trig_functions(trig.x_angle, turn.x_angle);
    get_trig_functions(trig.y_angle, turn.y_angle);
    get_trig_functions(trig.z_angle, turn.z_angle);
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

    trig_val_t trig;
    convert_angle_to_triangle(trig, turn);
    for (size_t i = 0; i < points.size; i++)
    {
        point_turn(points.array[i], trig);
    }

    return ERR_OK;
}
