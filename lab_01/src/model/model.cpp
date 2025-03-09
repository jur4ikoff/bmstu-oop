#include "model.hpp"
#include "constants.hpp"
#include "edges.hpp"
#include "errors.hpp"
#include "point.hpp"
#include "points.hpp"

#include "QDebug"
#include <cstdio>

/**
 * @brief Функция инициализирует модель
 */
model_t init(void)
{
    model_t model = { 0 };
    model.points = points_init();
    model.edges = edges_init();
    default_point(model.center);

    return model;
}

// Освобождение модели
void free_model(model_t &model)
{
    points_free(model.points);
    edges_free(model.edges);
}

// Определяет пустая ли модель или нет. 1 если пустая, иначе 0
bool model_is_empty(const model_t &model)
{
    if (points_is_empty(model.points) && edges_is_empty(model.edges))
        return true;

    return false;
}

/**
 * @brief Функция считывает данные из файла и записывает их в temp_model
 * @param[out] temp_model ссылка на структуру для записи
 * @param[in, out] file Файловый дескриптер
 */
static err_t _load_model(model_t &temp_model, FILE *file)
{
    if (file == NULL || !model_is_empty(temp_model))
        return ERR_ARGS;

    err_t rc = ERR_OK;
    points_t points = points_init();
    size_t points_count = 0;
    if ((rc = load_points(points, file)) == ERR_OK)
    {
        temp_model.points = points;

        edges_t edges = edges_init();
        if ((rc = load_edges(edges, file)) != ERR_OK)
        {
            points_free(points);
        }
        else
        {
            temp_model.edges = edges;
        }
    }

    return rc;
}

/**
 * @brief Функция загружает данные из файла в структуру типа model_t
 * @param[out] model Объект типа model_t для записи данных из файла, изменяемый параметр
 * @param[in] filename Имя файла для чтения
 */
err_t load_model(model_t &model, const filename_t &filename)
{
    err_t rc = ERR_OK;

    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        // Инициализируем временную модель
        model_t temp_model = init();
        rc = _load_model(temp_model, file);
        fclose(file);

        if (rc == ERR_OK)
        {
            free_model(model);
            model = temp_model;
        }
    }
    else
    {
        rc = ERR_FILE;
    }
    return rc;
}

/**
 * @brief Функция реализует сдвиг модели
 * @param[in, out] model Структура модели
 * @param[in] shift Данные для сдвига
 */
err_t shift_model(model_t &model, const shift_t &shift)
{
    err_t rc = ERR_OK;
    if (model.points.array && model.edges.array)
    {
        for (size_t i = 0; i < model.points.size; i++)
        {
            model.points.array[i].x += shift.x;
            model.points.array[i].y += shift.y;
            model.points.array[i].z += shift.z;
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
    if (model.points.array && model.edges.array)
    {
        for (size_t i = 0; i < model.points.size; i++)
        {
            model.points.array[i].x *= scale.x;
            model.points.array[i].y *= scale.y;
            model.points.array[i].z *= scale.z;
        }
    }
    else
        rc = ERR_EMPTY_MODEL;

    return rc;
}

// Функция для вычисления центра масс модели
point_t calculate_center(const model_t &model)
{
    point_t center = { 0, 0, 0 };
    if (model.points.size == 0)
    {
        return center;
    }

    for (size_t i = 0; i < model.points.size; ++i)
    {
        center.x += model.points.array[i].x;
        center.y += model.points.array[i].y;
        center.z += model.points.array[i].z;
    }

    center.x /= model.points.size;
    center.y /= model.points.size;
    center.z /= model.points.size;

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
    if (model.points.array == NULL || model.edges.array == NULL || model.points.size == 0)
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
    for (size_t i = 0; i < model.points.size; ++i)
    {
        rotate_x(model.points.array[i], x_angle, center);
        rotate_y(model.points.array[i], y_angle, center);
        rotate_z(model.points.array[i], z_angle, center);
    }

    return ERR_OK;
}
