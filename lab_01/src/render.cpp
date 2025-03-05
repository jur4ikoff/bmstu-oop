#include "render.hpp"
#include "model.hpp"
#include "errors.hpp"

#include <QPainter>
#include <QPixmap>

err_t render_model(const render_t &render, const model_t &model)
{
    QPainter painter(&render.plane);
    painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
    painter.drawLine(0, 0, 250, 500);
    (void)model;
    return ERR_OK;
}