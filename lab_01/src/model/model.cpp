#include "model.hpp"
#include "constants.hpp"
#include "edges.hpp"
#include "errors.hpp"
#include "model_actions.hpp"
#include "point.hpp"
#include "points.hpp"

#include "QDebug"
#include <cstdio>

/**
 * @brief Функция инициализирует модель
 */
model_t model_init(void)
{
    model_t model = { 0 };
    model.points = points_init();
    model.edges = edges_init();
    model.center = point_init();

    return model;
}

// Освобождение модели
void model_free(model_t &model)
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
static err_t _model_load(model_t &temp_model, FILE *file)
{
    if (file == NULL || !model_is_empty(temp_model))
        return ERR_ARGS;

    err_t rc = ERR_OK;
    points_t points = points_init();
    size_t points_count = 0;
    if ((rc = points_load(points, file)) == ERR_OK)
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
err_t model_load(model_t &model, const filename_t &filename)
{
    err_t rc = ERR_OK;

    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        // Инициализируем временную модель
        model_t temp_model = model_init();
        rc = _model_load(temp_model, file);
        fclose(file);

        if (rc == ERR_OK)
        {
            model_free(model);
            model = temp_model;
            rc = points_calculate_center(model.center, model.points);
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
err_t model_shift(model_t &model, const shift_t &shift)
{
    err_t rc = ERR_OK;
    if (!points_is_empty(model.points))
    {
        point_shift(model.center, shift);
        rc = points_shift(model.points, shift);
    }
    else
        rc = ERR_EMPTY_MODEL;

    return rc;
}

/**
 * @brief Функция реализует скейл
 * @param[in, out] model Структура модели
 * @param[in] scale Данные для скейла
 */
err_t model_scale(model_t &model, const scale_t &scale)
{
    err_t rc = ERR_OK;

    if (!points_is_empty(model.points))
    {
        if ((rc = points_scale(model.points, scale, model.center)) == ERR_OK)
        {
            // Если скейл, тогда обновляем центр, потому что онг может немного сдвинуться
            rc = points_calculate_center(model.center, model.points);
        }
    }
    else
        rc = ERR_EMPTY_MODEL;

    return rc;
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

/**
 * @brief Функция реализует поворот модели
 */
err_t model_turn(model_t &model, const turn_t &turn)
{
    // if (std::isnan(turn.x_angle) || std::isnan(turn.y_angle) || std::isnan(turn.z_angle)) {
    //     return ERR_ARGS;
    // }

    // Вычисляем центр масс модели
    point_t center = model.center;

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
