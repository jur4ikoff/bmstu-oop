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
    case ERR_FILE_CONTENT:
        QMessageBox::warning(NULL, "Ошибка", "Неверное содержимое файла");
    case ERR_FILE_EMPTY:
        QMessageBox::warning(NULL, "Ошибка", "Файл пустой");
    default:
        break;
    }
}