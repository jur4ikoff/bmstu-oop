#include "base_exception.h"

class BadCountError : public BaseContainerError
{
public:
    BadCountError(const char *filename,
                  const char *classname,
                  int line,
                  const char *time,
                  const char *message = "Error, Count less than one!") : BaseContainerError(filename, classname, line, time, message) {};
};