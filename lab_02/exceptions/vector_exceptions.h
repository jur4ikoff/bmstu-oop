#pragma once

#include "base_exceptions.h"

class errMemory : public BaseContainerError
{
public:
    errMemory(const char *file_name,
              int line,
              const char *class_name,
              const char *time,
              const char *inf = "Memory allocation error!")
        : BaseContainerError(file_name, line, class_name, time, inf) {};
};
