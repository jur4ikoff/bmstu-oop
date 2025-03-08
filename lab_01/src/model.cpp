#include "model.hpp"
#include "constants.hpp"
#include "errors.hpp"

#include "QDebug"
#include <cstdio>

model_t init(void)
{
    model_t model = {0};
    return model;
}

void free_model(model_t &model)
{
    if (model.edges)
        free(model.edges);

    if (model.points)
        free(model.points);
}

/**
 * @brief Функция реализует сдвиг модели
 * @param[out] model Структура модели
 * @param[in] shift Данные для сдвига
 */
err_t shift_model(model_t &model, const shift_t &shift)
{
    err_t rc = ERR_OK;
    if (model.points && model.edges)
    {
        for (size_t i = 0; i < model.points_count; i++)
        {
            model.points[i].x += shift.x;
            model.points[i].y += shift.y;
            model.points[i].z += shift.z;
        }
    }
    else
        rc = ERR_EMPTY_MODEL;

    return rc;
}

/**
 * @brief Функция реализует скейл
 * @param[out] model Структура модели
 * @param[in] scale Данные для скейла
 */
err_t scale_model(model_t &model, const scale_t &scale)
{
    err_t rc = ERR_OK;
    if (model.points && model.edges)
    {
        for (size_t i = 0; i < model.points_count; i++)
        {
            model.points[i].x *= scale.x;
            model.points[i].y *= scale.y;
            model.points[i].z *= scale.z;
        }
    }
    else
        rc = ERR_EMPTY_MODEL;

    return rc;
}

// Функция для вычисления центра масс модели
point_t calculate_center(const model_t &model)
{
    point_t center = {0, 0, 0};
    if (model.points_count == 0)
    {
        return center;
    }

    for (size_t i = 0; i < model.points_count; ++i)
    {
        center.x += model.points[i].x;
        center.y += model.points[i].y;
        center.z += model.points[i].z;
    }

    center.x /= model.points_count;
    center.y /= model.points_count;
    center.z /= model.points_count;

    return center;
}

// Функция для поворота точки вокруг оси X
void rotate_x(point_t &point, double angle, const point_t &center)
{
    double y = point.y - center.y;
    double z = point.z - center.z;
    point.y = center.y + y * cos(angle) - z * sin(angle);
    point.z = center.z + y * sin(angle) + z * cos(angle);
}

// Функция для поворота точки вокруг оси Y
void rotate_y(point_t &point, double angle, const point_t &center)
{
    double x = point.x - center.x;
    double z = point.z - center.z;
    point.x = center.x + x * cos(angle) + z * sin(angle);
    point.z = center.z - x * sin(angle) + z * cos(angle);
}

// Функция для поворота точки вокруг оси Z
void rotate_z(point_t &point, double angle, const point_t &center)
{
    double x = point.x - center.x;
    double y = point.y - center.y;
    point.x = center.x + x * cos(angle) - y * sin(angle);
    point.y = center.y + x * sin(angle) + y * cos(angle);
}

// Основная функция для поворота модели
err_t turn_model(model_t &model, const turn_t &turn)
{
    if (model.points == nullptr || model.edges == nullptr || model.points_count == 0)
    {
        return ERR_ARGS;
    }

    // if (std::isnan(turn.x_angle) || std::isnan(turn.y_angle) || std::isnan(turn.z_angle)) {
    //     return ERR_ARGS;
    // }

    // Вычисляем центр масс модели
    point_t center = calculate_center(model);

    // Преобразуем углы из градусов в радианы
    double x_angle = turn.x_angle * M_PI / 180.0;
    double y_angle = turn.y_angle * M_PI / 180.0;
    double z_angle = turn.z_angle * M_PI / 180.0;

    // Применяем поворот к каждой точке
    for (size_t i = 0; i < model.points_count; ++i)
    {
        rotate_x(model.points[i], x_angle, center);
        rotate_y(model.points[i], y_angle, center);
        rotate_z(model.points[i], z_angle, center);
    }

    return ERR_OK;
}