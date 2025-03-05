#include "render.hpp"
#include "model.hpp"
#include "errors.hpp"
#include "constants.hpp"

#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <cstdio>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

/**
 * @brief Функция ищет минимальное значение точки по координате х, y в массиве точек
 * @param[out] min_value Минимальное значение по координате х, y в массиве точек
 * @param[in] arr Массив точек
 */
static err_t get_min_point_coord(double &min_value, const point_t *const arr, const size_t size)
{
    err_t rc = ERR_OK;
    double temp_min = INF;
    if (arr)
    {
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i].x < temp_min)
                temp_min = arr[i].x;

            if (arr[i].y < temp_min)
                temp_min = arr[i].y;
        }
    }
    else
        rc = ERR_ARGS;

    min_value = temp_min;
    return rc;
}

/**
 * @brief Функция ищет максимальное значение точки по координате х, y в массиве точек
 * @param[out] min_value Минимальное значение по координате х, y в массиве точек
 * @param[in] arr Массив точек
 */
static err_t get_max_point_coord(double &max_value, const point_t *const arr, const size_t size)
{
    err_t rc = ERR_OK;
    double temp_max = NINF;
    if (arr)
    {
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i].x > temp_max)
                temp_max = arr[i].x;

            if (arr[i].y > temp_max)
                temp_max = arr[i].y;
        }
    }
    else
        rc = ERR_ARGS;

    max_value = temp_max;
    return rc;
}

/**
 * @brief Функция ищет нужный масштаб, для отрисовки на QPixmap
 * @param[out] scale В ссылку scale записывается маcштаб
 * @param[in] model Данные, для поиска
 * @param[in] window_size Размер окна, для определения масштаба
 */
static err_t get_scale(double &scale, const model_t &model, const double window_size)
{
    err_t rc = ERR_OK;
    double min_coord, max_coord;
    rc = get_min_point_coord(min_coord, model.points, model.points_count);
    if (!rc)
    {
        rc = get_max_point_coord(max_coord, model.points, model.points_count);
        if (!rc)
        {
            // Задаем масштаб
            double delta = max_coord - min_coord;
            min_coord -= delta * 0.1;
            max_coord += delta * 0.1;

            delta = max_coord - min_coord;
            qDebug() << "min " << min_coord << " max" << max_coord;
            if (delta != 0)
                scale = window_size / (max_coord - min_coord);
            else
                scale = 1;
        }
    }

    return rc;
}

/**
 * @brief Функция для отрисовки модели
 * @param[in] render Холст и его размеры
 * @param[in] model Данные для отрисовки
 */
err_t render_model(const render_t &render, const model_t &model)
{
    // Обновляем QPixmap
    render.plane.fill("#252525");
    QPainter painter(&render.plane);

    err_t rc = ERR_OK;
    double scale = 0;

    if ((rc = get_scale(scale, model, MAX(render.width, render.height))) == ERR_OK)
    {
        qDebug() << "scale " << scale;
        for (size_t i = 0; i < model.points_count; i++)
        {
            printf("%.2f %.2f %.2f\n", model.points[i].x, model.points[i].y, model.points[i].z);
        }

        for (size_t i = 0; i < model.edges_count; i++)
        {
            printf("%zu %zu\n", model.edges[i].first, model.edges[i].second);
        }
        // painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
        // painter.drawLine(0, 0, 250, 500);
    }
    return rc;
}