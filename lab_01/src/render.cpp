#include "render.hpp"
#include "points.hpp"
#include "constants.hpp"
#include "errors.hpp"
#include "model.hpp"

#include <QColor>
#include <QPainter>
#include <QPixmap>
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
static err_t get_scale(double &scale, const model_t &model, const int window_size)
{
    err_t rc = ERR_OK;
    double min_coord, max_coord;
    rc = get_min_point_coord(min_coord, model.points.array, model.points.size);
    if (!rc)
    {
        rc = get_max_point_coord(max_coord, model.points.array, model.points.size);
        if (!rc)
        {
            // Задаем масштаб
            double delta = max_coord - min_coord;
            min_coord -= delta * 0.1;
            max_coord += delta * 0.1;

            delta = max_coord - min_coord;
            if (delta != 0)
                scale = (double)window_size / (max_coord - min_coord);
            else
                scale = 1;
        }
    }

    return rc;
}

void drawPointsOnPixmap(QPainter &painter, const point_t *points, size_t pointsCount, double scale, const int &windowSize)
{
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::blue);

    // Рисуем точки
    for (size_t i = 0; i < pointsCount; ++i)
    {
        QPointF scaledPoint(
            windowSize / 2.0 + (points[i].x) * scale,
            windowSize / 2.0 - (points[i].y) * scale);
        painter.drawEllipse(scaledPoint, 2, 2);
    }
}

// Функция для отрисовки линий между точками на QPixmap (без отступов)
void drawEdgesOnPixmap(QPainter &painter, const point_t *points, size_t pointsCount, const edge_t *edges, size_t edgesCount, double scale, const int &windowSize)
{
    painter.setRenderHint(QPainter::Antialiasing, true); // Включаем сглаживание

    // Устанавливаем цвет и толщину линии
    painter.setPen(QPen(Qt::white, 1)); // Черные линии толщиной 2 пикселя

    // Рисуем линии между точками
    for (size_t i = 0; i < edgesCount; ++i)
    {
        // Получаем индексы начальной и конечной точек
        size_t startIndex = edges[i].first;
        size_t endIndex = edges[i].second;

        // Проверяем, что индексы корректны
        if (startIndex >= pointsCount || endIndex >= pointsCount)
        {
            qWarning() << "Неверный индекс ребра:" << i;
            continue;
        }

        // Масштабируем координаты и смещаем их относительно центра
        // Фикс
        QPointF startPoint(
            windowSize / 2.0 + (points[startIndex].x) * scale,
            windowSize / 2.0 - (points[startIndex].y) * scale);

        QPointF endPoint(
            windowSize / 2.0 + (points[endIndex].x) * scale,
            windowSize / 2.0 - (points[endIndex].y) * scale);

        // Рисуем линию между точками
        painter.drawLine(startPoint, endPoint);
    }
}

/**
 * @brief Функция для отрисовки модели
 * @param[in] render Холст и его размеры
 * @param[in] model Данные для отрисовки
 */
err_t render_model(const render_t &render, const model_t &model)
{
    err_t rc = ERR_OK;
    // Обновляем QPixmap
    if (render.plane)
    {
        // НАПИСАТЬ ПРОВЕРКУ НА МОДЕЛЬ
        render.plane->fill("#252525");
        QPainter painter(render.plane);
        int window_size = MAX(render.width, render.height);

        double scale = (window_size) / 6;

        drawPointsOnPixmap(painter, model.points.array, model.points.size, scale, window_size);
        // Сделать функцию скейла СПРОСИТЬ У ВАНИ
        drawEdgesOnPixmap(painter, model.points.array, model.points.size, model.edges.array, model.edges.size, scale, window_size);
        painter.end();
    }
    else
        rc = ERR_ARGS;
    return rc;
}
