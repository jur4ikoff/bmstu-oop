#include "request.hpp"
#include "model.hpp"
#include "render.hpp"

#include <QDebug>

err_t request_handler(const request_t &request)
{
    err_t rc = ERR_OK;
    static model_t model = init();

    switch (request.task)
    {
    case REQ_LOAD:
        qDebug() << "LOAD FILE " << request.filename;
        rc = load_model(model, request.filename);
        break;
    case REQ_SHIFT:
        qDebug() << "REQ_SHIFT";
        break;
    case REQ_TURN:
        qDebug() << "REQ_TURN";
        break;
    case REQ_SCALE:
        qDebug() << "REQ_SCALE";
        break;
    case REQ_RENDER:
        rc = render_model(request.render, model);
        qDebug() << "REQ_DRAW";
        break;
    case REQ_QUIT:
        qDebug() << "REQ_QUIT";
        free_model(model);
        break;
    default:
        rc = ERR_UNKNOWN_COMMAND;
    }

    return rc;
}
