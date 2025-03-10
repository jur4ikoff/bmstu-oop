#include "utils.hpp"
#include "errors.hpp"

#include <QByteArray>
#include <QString>
#include <cstdio>

/**
 * @brief Функция конвертирует объект типа QString в const char
 * @param[in] to_convert
 */
const char *convert_QString_to_char(const QString &to_convert)
{
    QByteArray byte_array = to_convert.toUtf8();
    const char *char_ptr = byte_array.constData();
    char *mod_ptr = new char[byte_array.size() + 1];
    std::strcpy(mod_ptr, char_ptr);
    return mod_ptr;
}

/**
 * @brief Функция читает из файла целое положительное число
 * @param[out] number Прочитанное число
 * @param[in, out] file ИЗМЕНЯЕМЫЙ. Указатель на файловый дескриптор
 */
err_t read_int_number(size_t &number, FILE *file)
{
    if (file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;

    int temp;
    int read = fscanf(file, "%d", &temp);
    if (read != 1)
        rc = ERR_FILE_CONTENT;
    else
    {
        if (temp < 0)
            rc = ERR_FILE_CONTENT;
        else
            number = (size_t)temp;
    }

    return rc;
}

/**
 * @brief Функция читает количество элементов в файле, если их меньше 1, то возвращается ошибка
 * @param[out] count Количество граней в моделе
 * @param[in, out] file файловый дескриптор
 */
err_t read_elements_count(size_t &count, FILE *file)
{
    if (file == NULL)
        return ERR_ARGS;

    err_t rc = ERR_OK;
    if ((rc = read_int_number(count, file)) == ERR_OK)
    {
        if (count < 1)
            rc = ERR_ARRAY_EMPTY;
    }

    return rc;
}
