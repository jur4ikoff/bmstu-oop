#ifndef ERRORS_H__
#define ERRORS_H__

typedef enum
{
    ERR_OK,
    ERR_FILE,
    ERR_FILE_OPEN,
    ERR_FILE_CONTENT,
} err_t;

void error_handler(const err_t);

#endif