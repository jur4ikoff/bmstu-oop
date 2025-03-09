#include "edges.hpp"
#include "errors.hpp"
#include "model.hpp"
#include "point.hpp"
#include "points.hpp"
#include "utils.hpp"

#include <QDebug>
#include <cstdio>
#include <stdlib.h>

/**
 * @brief Функция считывает данные из файла и записывает их в temp_model
 * @param[out] temp_model ссылка на структуру для записи
 * @param[in, out] file Файловый дескриптер
 */
static err_t _load_model(model_t &temp_model, FILE *file)
{
    if (file == NULL)
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
