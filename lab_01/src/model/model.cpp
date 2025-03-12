#include "model.hpp"
#include "constants.hpp"
#include "edges.hpp"
#include "errors.hpp"
#include "model_actions.hpp"
#include "point.hpp"
#include "points.hpp"

#include <QDebug>
#include <cstdio>

/**
 * @brief Фунекция получает значение, на которое нужно сдвинуть фигуру, чтобы ее центр был в 0, 0
 * @param[out] shift Смещение
 * @param[in] center точка, центр
 * @return Смещение
 */
static void get_shift(shift_t &shift, const point_t &center)
{
    shift.x = -center.x;
    shift.y = -center.y;
    shift.z = -center.z;
}

/**
 * @brief Функция умножает каждую координату на -1
 * @param[in, out] shift Структура смещения
 */
static void get_shift_back(shift_t &shift)
{
    shift.x *= -1;
    shift.y *= -1;
    shift.z *= -1;
}

/**
 * @brief Функция инициализирует модель
 */
model_t model_init(void)
{
    model_t model = {0};
    model.points = points_init();
    model.edges = edges_init();

    point_set_default_value(model.center);
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
    if (points_is_empty(model.points) || edges_is_empty(model.edges))
        return true;

    return false;
}

/**
 * @brief Фукнкция валидирует модель
 * @param[in] edges Структура граней
 * @param[in] points Структура точек
 */
err_t model_validate_content(const edges_t &edges, const points_t &points)
{
    return edges_validate(edges, points.size);
}

/**
 * @brief Фукнкция валидирует модель
 * @param[in] model ссылка на структуру с моделью
 */
err_t model_validate(const model_t &model)
{
    return model_validate_content(model.edges, model.points);
}

/**
 * @brief Функция считывает данные из файла и записывает их в temp_model
 * @param[out] temp_model ссылка на структуру для записи
 * @param[in, out] file Файловый дескриптер
 */
static err_t model_load_content(model_t &temp_model, FILE *file)
{
    if (file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    if ((rc = points_load(temp_model.points, file)) == ERR_OK)
    {
        if ((rc = edges_load(temp_model.edges, file)) == ERR_OK)
        {
            rc = points_calculate_center(temp_model.center, temp_model.points);
        }
    }

    if (rc != ERR_OK)
    {
        points_free(temp_model.points);
        edges_free(temp_model.edges);
    }

    return rc;
}

/**
 * @brief Функция загружает данные из файла в структуру типа model_t
 * @param[in, out] model Объект типа model_t для записи данных из файла, изменяемый параметр
 * @param[in] filename Имя файла для чтения
 */
err_t model_load(model_t &model, const filename_t &filename)
{
    err_t rc = ERR_OK;
    // Определяем временную модель, потому что основная это var параметр, и меняется только при успешном считываними
    model_t temp_model;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        rc = ERR_FILE;
    }
    else
    {
        rc = model_load_content(temp_model, file);
        fclose(file);
        if (rc == ERR_OK)
        {
            rc = model_validate(temp_model);
            if (rc != ERR_OK)
                model_free(temp_model);
            else
            {
                model_free(model);
                model = temp_model;
            }
        }
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
    if (points_is_empty(model.points))
        return ERR_EMPTY_MODEL;

    err_t rc = points_shift(model.points, shift);
    if (rc == ERR_OK)
        point_shift(model.center, shift);

    return rc;
}

/**
 * @brief Функция реализует скейл
 * @param[in, out] model Структура модели
 * @param[in] scale Данные для скейла
 */
err_t model_scale(model_t &model, const scale_t &scale)
{
    if (points_is_empty(model.points))
        return ERR_EMPTY_MODEL;

    shift_t shift;
    get_shift(shift, model.center);
    point_shift(model.center, shift);
    err_t rc = points_shift(model.points, shift);
    if (rc == ERR_OK)
    {
        rc = points_scale(model.points, scale);
        if (rc == ERR_OK)
        {
            get_shift_back(shift);
            point_shift(model.center, shift);
            rc = points_shift(model.points, shift);
            if (rc == ERR_OK)
                rc = points_calculate_center(model.center, model.points);
        }
    }

    return rc;
}

/**
 * @brief Функция реализует поворот модели
 * @param[in, out] model Ссылка на модель
 * @param[in] turn Структура с данными о повороте
 */
err_t model_turn(model_t &model, const turn_t &turn)
{
    if (points_is_empty(model.points))
        return ERR_EMPTY_MODEL;

    shift_t shift;
    get_shift(shift, model.center);

    point_shift(model.center, shift);
    err_t rc = points_shift(model.points, shift);
    if (rc == ERR_OK)
    {
        rc = points_turn(model.points, turn);
        if (rc == ERR_OK)
        {
            get_shift_back(shift);
            point_shift(model.center, shift);
            rc = points_shift(model.points, shift);
        }
    }

    return rc;
}
