#include "model.hpp"
#include "constants.hpp"
#include "edges.hpp"
#include "errors.hpp"
#include "model_actions.hpp"
#include "point.hpp"
#include "points.hpp"

#include <cstdio>

/**
 * @brief Фунекция получает значение, на которое нужно сдвинуть фигуру, чтобы ее центр был в 0, 0
 * @param[in] center точка, центр
 * @return Смещение
 */
static shift_t get_shift(const point_t &center)
{
    shift_t shift = {};
    shift.x = -center.x;
    shift.y = -center.y;
    shift.z = -center.z;

    return shift;
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
 * @brief Фукнкция валидирует модель
 * @param[in] edges Структура граней
 * @param[in] points Структура точек
 */
static err_t model_validate_content(const edges_t &edges, const points_t &points)
{
    if (edges.array == NULL)
        return ERR_ARGS;

    err_t rc = edges_validate(edges, points.size);
    return rc;
}

/**
 * @brief Фукнкция валидирует модель
 * @param[in] model ссылка на структуру с моделью
 */
err_t model_validate(const model_t &model)
{
    err_t rc = model_validate_content(model.edges, model.points);
    return rc;
}

/**
 * @brief Функция считывает данные из файла и записывает их в temp_model
 * @param[out] temp_model ссылка на структуру для записи
 * @param[in, out] file Файловый дескриптер
 */
static err_t model_load_elements(model_t &temp_model, FILE *file)
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
            rc = model_validate(temp_model);
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
        rc = model_load_elements(temp_model, file);
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

/**
 * @brief Функция реализует поворот модели
 * @param[in, out] model Ссылка на модель
 * @param[in] turn Структура с данными о повороте
 */
err_t model_turn(model_t &model, const turn_t &turn)
{
    err_t rc = ERR_OK;
    if (!model_is_empty(model))
    {
        shift_t shift = get_shift(model.center);
        if ((rc = model_shift(model, shift)) == ERR_OK)
        {
            if ((rc = points_turn(model.points, turn)) == ERR_OK)
            {
                get_shift_back(shift);
                rc = model_shift(model, shift);
            }
        }
    }
    else
    {
        rc = ERR_EMPTY_MODEL;
    }

    return rc;
}
