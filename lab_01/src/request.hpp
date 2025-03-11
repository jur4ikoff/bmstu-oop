#ifndef REQUEST_H__
#define REQUEST_H__

#include "errors.hpp"
#include "model.hpp"
#include "render.hpp"

typedef enum
{
    REQ_LOAD,
    REQ_SHIFT,
    REQ_TURN,
    REQ_SCALE,
    REQ_RENDER,
    REQ_QUIT,
} req_type;

typedef int quit_t; // Чтобы компилятор не ругался

typedef struct
{
    req_type task;

    union
    {
        filename_t filename;
        render_t render;
        shift_t shift;
        scale_t scale;
        turn_t turn;
        quit_t quit; // Чтобы компилятор не ругался
    };

} request_t;

err_t request_handler(const request_t &);

#endif // REQUEST_H__
