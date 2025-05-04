#pragma once

#include "base_exceptions.h"

class errMemory : public BaseContainerError
{
public:
    errMemory(const char *filename,
              int line,
              const char *class_name,
              const char *time,
              const char *err_msg = "Ошибка выделения памяти")
        : BaseContainerError(filename, line, class_name, time, err_msg) {};
};

class errDeletedVector : public BaseContainerError
{
public:
    errDeletedVector(const char *filename,
                     int line,
                     const char *class_name,
                     const char *time,
                     const char *err_msg = "Ошибка, использование удаленного вектора")
        : BaseContainerError(filename, line, class_name, time, err_msg) {};
};

class errIndexOutOfRange : public BaseContainerError
{
public:
    errIndexOutOfRange(const char *filename,
                       int line,
                       const char *class_name,
                       const char *time,
                       const char *err_msg = "Ошибка, индекс иттератора вышел за пределы контейнера")
        : BaseContainerError(filename, line, class_name, time, err_msg) {};
};

class errNegSize : public BaseContainerError
{
public:
    errNegSize(const char *filename,
                       int line,
                       const char *class_name,
                       const char *time,
                       const char *err_msg = "Ошибка, отрицательные размер")
        : BaseContainerError(filename, line, class_name, time, err_msg) {};
};
