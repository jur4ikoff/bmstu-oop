
// #pragma once

// #include "base_exceptions.h"

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