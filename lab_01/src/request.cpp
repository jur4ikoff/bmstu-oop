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
            rc = turn_model(model, request.turn);
            break;
        case REQ_SCALE:
            rc = scale_model(model, request.scale);
            break;
        case REQ_RENDER:
            rc = render_model(request.render, model);
            break;
        case REQ_QUIT:
            model_free(model);
            break;
        default:
            rc = ERR_UNKNOWN_COMMAND;
    }

    return rc;
}
