#ifndef ERRORS_H__
#define ERRORS_H__

typedef enum
{
    ERR_OK,
    ERR_FILE,
    ERR_FILE_OPEN,
    ERR_FILE_CONTENT,
    ERR_ARRAY_EMPTY,
    ERR_UNKNOWN_COMMAND,
    ERR_WRONG_INPUT_LABEL,
    ERR_EMPTY_MODEL,
    ERR_MEMORY_ALLOCATION, 
    ERR_ARGS, ERR_EDGES
} err_t;

void error_handler(const err_t);

#endif
