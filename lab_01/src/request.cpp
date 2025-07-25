#include "request.hpp"
#include "model.hpp"
#include "render.hpp"

#include <QDebug>

err_t request_handler(const request_t &request)
{
    err_t rc = ERR_OK;
    static model_t model = model_init();

    switch (request.task)
    {
    case REQ_LOAD:
        rc = model_load(model, request.filename);
        break;
    case REQ_SHIFT:
        rc = model_shift(model, request.shift);
        break;
    case REQ_TURN:
        rc = model_turn(model, request.turn);
        break;
    case REQ_SCALE:
        rc = model_scale(model, request.scale);
        break;
    case REQ_RENDER:
        rc = model_render(request.render, model);
        break;
    case REQ_QUIT:
        model_free(model);
        break;
    default:
        rc = ERR_UNKNOWN_COMMAND;
    }

    return rc;
}
