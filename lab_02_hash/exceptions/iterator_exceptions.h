
#pragma once

#include "base_exception.h"

// // Ошибка, возникает при попытке получить доступ к weak_ptr, который не содержит в себе  "указатель" на контейнер
// class errDeletedVector : public BaseContainerError
// {
// public:
//     errDeletedVector(const char *filename,
//                      int line,
//                      const char *class_name,
//                      const char *time,
//                      const char *err_msg = "Ошибка, использование удаленного вектора")
//         : BaseContainerError(filename, line, class_name, time, err_msg) {};
// };

// class errIndexOutOfRange : public BaseContainerError
// {
// public:
//     errIndexOutOfRange(const char *filename,
//                        int line,
//                        const char *class_name,
//                        const char *time,
//                        const char *err_msg = "Ошибка, индекс итератора вышел за пределы контейнера")
//         : BaseContainerError(filename, line, class_name, time, err_msg) {};
// };

// Итераторы

class IteratorTableWasChanged : public BaseError
{
public:
    IteratorTableWasChanged(const char *filename, const char *classname, int line_num, const char *message = "Iterator is not valid (hash table was changed)!") : BaseError(filename, classname, line_num, message) {};
};

class IteratorNoDataFound : public BaseError
{
public:
    IteratorNoDataFound(const char *filename, const char *classname, int line_num, const char *message = "Iterator is not valid (hash table was changed)!") : BaseError(filename, classname, line_num, message) {};
};

class IteratorDoesntExistError : public BaseError
{
public:
    IteratorDoesntExistError(const char *filename, const char *classname, int line_num, const char *message = "Iterator is linked to a hash table that doesn't exist!") : BaseError(filename, classname, line_num, message) {};
};
