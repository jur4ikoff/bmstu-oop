#include "request.hpp"
#include <QDebug>

err_t request_handler(const request_t &request)
{
    err_t return_code = ERR_OK;
    switch (request.task)
    {
        case REQ_LOAD:
            qDebug() << "Load";
            break;
        case REQ_SHIFT:
            qDebug() << "SHIFT";
            break;
        case REQ_TURN:
            qDebug() << "REQ_TURN";
            break;
        case REQ_SCALE:
            qDebug() << "REQ_SCALE";
            break;
        case REQ_DRAW:
            qDebug() << "REQ_DRAW";
            break;
        case REQ_QUIT:
            qDebug() << "REQ_QUIT";
            break;
        default:
            return_code = ERR_UNKNOWN_COMMAND;
    }

    return return_code;
}
