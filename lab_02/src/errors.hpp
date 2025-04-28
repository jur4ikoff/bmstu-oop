#ifndef ERRORS_H__
#define ERRORS_H__

enum _err_type
{
    ERR_OK,
};

using err_t = _err_type;

void error_handler(const err_t);

#endif
