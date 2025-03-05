#include "model.hpp"
#include "errors.hpp"

#include <cstdio>
#include "QDebug"

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
 * @param[in] scale Данные для сдвига
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