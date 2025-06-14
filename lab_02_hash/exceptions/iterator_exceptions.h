
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

// Итераторы

class IteratorIndexOutOfRange : public BaseIteratorError
{
public:
    IteratorIndexOutOfRange(const char *filename,
                            const char *class_name,
                            int line,
                            const char *time,
                            const char *message = "Ошибка, индекс итератора вышел за пределы контейнера")
        : BaseIteratorError(filename, class_name, line, time, message) {};
};

class IteratorTableWasChanged : public BaseIteratorError
{
public:
    IteratorTableWasChanged(const char *filename,
                            const char *class_name,
                            int line,
                            const char *time,
                            const char *message = "Iterator is not valid (hash table was changed)!")
        : BaseIteratorError(filename, class_name, line, time, message) {};
};

class IteratorNoDataFound : public BaseIteratorError
{
public:
    IteratorNoDataFound(const char *filename,
                        const char *class_name,
                        int line,
                        const char *message = "Iterator is not valid (hash table was changed)!")
        : BaseIteratorError(filename, class_name, line, message) {};
};

class IteratorDoesntExistError : public BaseIteratorError
{
public:
    IteratorDoesntExistError(const char *filename,
                             const char *class_name,
                             int line,
                             const char *time,
                             const char *message = "Iterator is linked to a hash table that doesn't exist!")
        : BaseIteratorError(filename, class_name, line, time, message) {};
};

// class errIndexOutOfRange : public BaseIteratorError
// {
// public:
//     errIndexOutOfRange(const char *filename,
//                        int line,
//                        const char *class_name,
//                        const char *time,
//                        const char *err_msg = "Ошибка, индекс итератора вышел за пределы контейнера")
//         : BaseIteratorError(filename, line, class_name, time, err_msg) {};
// };
