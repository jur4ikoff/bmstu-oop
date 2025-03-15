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
        QMessageBox::warning(NULL, "Ошибка", "Ошибка, неверно определена модель. Проверьте корректность точек и граней");
        break;
    case ERR_ARRAY_EMPTY:
        QMessageBox::warning(NULL, "Ошибка", "Массив точек или ребер - пустой");
        break;
    case ERR_ARGS:
        QMessageBox::warning(NULL, "Ошибка", "Произошла ошибка при передаче параметров в функцию");
        break;
    case ERR_WRONG_INPUT_LABEL:
        QMessageBox::warning(NULL, "Ошибка", "Введено неверное значение");
        break;
    case ERR_EMPTY_MODEL:
        QMessageBox::warning(NULL, "Ошибка", "Ошибка, действие невозможно. Модель пустая");
        break;
    case ERR_MEMORY_ALLOCATION:
        QMessageBox::warning(NULL, "Ошибка", "Ошибка при выделении памяти");
        break;
    case ERR_EDGES:
        QMessageBox::warning(NULL, "Ошибка", "Ошибка, задан неверный индекс грани");
        break;
    case ERR_LINE:
        QMessageBox::warning(NULL, "Ошибка", "Ошибка, неверная линия");
        break;
    default:
        break;
    }
}
