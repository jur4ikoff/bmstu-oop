#pragma once

#include "base_exception.h"

// class errNegSize : public BaseContainerError
// {
// public:
//     errNegSize(const char *filename,
//                int line,
//                const char *class_name,
//                const char *time,
//                const char *err_msg = "Ошибка, неверный размер вектора")
//         : BaseContainerError(filename, line, class_name, time, err_msg) {};
// };

// class errArrNull : public BaseContainerError
// {
// public:
//     errArrNull(const char *filename,
//                int line,
//                const char *class_name,
//                const char *time,
//                const char *err_msg = "Ошибка, указатель на массив = NULL, в конструктор нужно передать валидный массив.")
//         : BaseContainerError(filename, line, class_name, time, err_msg) {};
// };

// class errVectorsSizeNotEqual : public BaseContainerError
// {
// public:
//     errVectorsSizeNotEqual(const char *filename,
//                            int line,
//                            const char *class_name,
//                            const char *time,
//                            const char *err_msg = "Ошибка, векторы разного размера. Для запрашиваемой операции нужны векторы одинакового размера")
//         : BaseContainerError(filename, line, class_name, time, err_msg) {};
// };

// class errSizeNotCompatible : public BaseContainerError
// {
// public:
//     errSizeNotCompatible(const char *filename,
//                          int line,
//                          const char *class_name,
//                          const char *time,
//                          const char *err_msg = "Ошибка, размер векторов не подходит для выполнения данной операции")
//         : BaseContainerError(filename, line, class_name, time, err_msg) {};
// };

class MemoryError : public BaseError
{
public:
    MemoryError(const char *filename, const char *classname, int line_num, const char *message = "Memory allocation error!") : BaseError(filename, classname, line_num, message) {};
};

class BadCapacityError : public BaseError
{
public:
    BadCapacityError(const char *filename, const char *classname, int line_num, const char *message = "Capacity passed is less than one!") : BaseError(filename, classname, line_num, message) {};
};

class KeyNotFoundError : public BaseError
{
public:
    KeyNotFoundError(const char *filename, const char *classname, int line_num, const char *message = "Requested key was not found!") : BaseError(filename, classname, line_num, message) {};
};

class TableIndexOutOfRange : public BaseError
{
public:
    TableIndexOutOfRange(const char *filename, const char *classname, int line_num, const char *message = "Requested index is out of hash table range!") : BaseError(filename, classname, line_num, message) {};
};
