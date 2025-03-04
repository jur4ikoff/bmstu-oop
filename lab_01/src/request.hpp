#ifndef REQUEST_H__
#define REQUEST_H__

#include "errors.hpp"
#include "model.hpp"

typedef enum
{
    REQ_LOAD,
    REQ_SHIFT,
    REQ_TURN,
    REQ_SCALE,
    REQ_DRAW,
    REQ_QUIT,
    REQ_DEBUG, // Только в дебаг версии
} req_type;


typedef struct _request_type_
{
    req_type task;
    union 
    {
        filename_t filename;
        /* data */
    };
    
}request_t;

err_t request_handler(const request_t &);

#endif // REQUEST_H__
