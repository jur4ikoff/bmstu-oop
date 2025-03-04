#include "errors.hpp"

#include <QMessageBox>

void error_handler(const err_t error_code)
{
    switch (error_code)
    {
    case ERR_FILE:
        QMessageBox::critical(NULL, "Ошибка", "Не удалось выбрать файл");
        break;
    case ERR_FILE_OPEN:
        QMessageBox::critical(NULL, "Ошибка", "Не удалось открыть файл");
        break;
    case ERR_FILE_CONTENT:
        QMessageBox::warning(NULL, "Ошибка", "Неверное содержимое файла");
        break;
    case ERR_ARRAY_EMPTY:
        QMessageBox::warning(NULL, "Ошибка", "Массив точек или ребер - пустой");
        break;
    case ERR_ARGS:
        QMessageBox::warning(NULL, "Ошибка", "Произошла ошибка при передаче параметров в функцию");
        break;
    default:
        break;
    }
}