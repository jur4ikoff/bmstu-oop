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
               const char *err_msg = "Ошибка, неверный размер вектора")
        : BaseContainerError(filename, line, class_name, time, err_msg) {};
};

class errArrNull : public BaseContainerError
{
public:
    errArrNull(const char *filename,
               int line,
               const char *class_name,
               const char *time,
               const char *err_msg = "Ошибка, указатель на массив = NULL, в конструктор нужно передать валидный массив.")
        : BaseContainerError(filename, line, class_name, time, err_msg) {};
};

class errDivisionZero : public BaseContainerError
{
public:
    errDivisionZero(const char *filename,
                    int line,
                    const char *class_name,
                    const char *time,
                    const char *err_msg = "Ошибка, деление на ноль")
        : BaseContainerError(filename, line, class_name, time, err_msg) {};
};

class errVectorsSizeNotEqual : public BaseContainerError
{
public:
    errVectorsSizeNotEqual(const char *filename,
                           int line,
                           const char *class_name,
                           const char *time,
                           const char *err_msg = "Ошибка, векторы разного размера. Для запрашиваемой операции нужны векторы одинакового размера")
        : BaseContainerError(filename, line, class_name, time, err_msg) {};
};

class errSizeNotCompatible : public BaseContainerError
{
public:
    errSizeNotCompatible(const char *filename,
                         int line,
                         const char *class_name,
                         const char *time, 
                         const char *err_msg = "Ошибка, размер векторов не подходит для выполнения данной операции")
        : BaseContainerError(filename, line, class_name, time, err_msg) {};
};


class errDifferentContainers : public BaseContainerError
{
public:
    errDifferentContainers(const char *filename,
                         int line,
                         const char *class_name,
                         const char *time, 
                         const char *err_msg = "Ошибка, разные контейнеры")
        : BaseContainerError(filename, line, class_name, time, err_msg) {};
};