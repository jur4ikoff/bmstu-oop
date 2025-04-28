#ifndef ERRORS_H__
#define ERRORS_H__

enum
{
    ERR_OK,
} _err_type;

using err_t = _err_type;

void error_handler(const err_t);

#endif
