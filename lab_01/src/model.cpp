#include "model.hpp"
#include "errors.hpp"

#include <cstdio>
#include "QDebug"

model_t init(void)
{
    model_t model = {0};
    return model;
}

/**
 * @brief Функция читает из файла все точки
 * @param[out] file ИЗМЕНЯЕМЫЙ - файловый дескриптер
 * @param[out] points ИЗМЕНЯЕМЫЙ - массив точек
 * @param[out] points_count Количество точек в массиве
 */
static err_t _load_points(FILE *file, point_t *points, size_t &points_count)
{
}

/**
 * @brief Функция считывает данные из файла и записывает их в temp_model
 * @param[out] temp_model ссылка на место для записи. Изменяемый параметр
 *  @param[in] f Файловый дескриптер
 */
static err_t _load_model(model_t &temp_model, FILE *file)
{
    err_t rc = ERR_OK;
    int points_count;

    temp_model.points_count = static_cast<int>(points_count);
    qDebug() << temp_model.points_count;

    return rc;
}

/**
 * @brief Функция загружает данные из файла в структуру типа model_t
 * @param[out] model Объект типа model_t для записи данных из файла, изменяемый параметр
 * @param[in] filename Имя файла для чтения
 */
err_t load_model(model_t &model, const filename_t &filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return ERR_FILE_OPEN;

    err_t rc = ERR_OK;
    model_t temp_model = init();
    rc = _load_model(temp_model, file);
    fclose(file);

    if (rc == ERR_OK)
    {
        free_model(model);
        model = temp_model;
    }
    return rc;
}

void free_model(model_t &model)
{
    if (model.edges)
        free(model.edges);

    if (model.points)
        free(model.points);
}