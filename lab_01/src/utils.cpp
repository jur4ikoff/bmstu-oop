#include "utils.hpp"
#include "errors.hpp"

#include <cstdio>
#include <QString>
#include <QByteArray>

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
 * @brief Функция читает из файла целое число
 * @param[out] file ИЗМЕНЯЕМЫЙ. Указатель на файловый дескриптор
 * @param[out] number Прочитанное число
 */
err_t read_int_number(FILE *file, int &number)
{
    rc = ERR_OK;
    int read = fscanf(file, "%d", &number);

    if (read != 1)
        rc = ERR_FILE;
    else
    {
        if (number < 1)
            rc = ERR_FILE_EMPTY;
    }

    return rc;
}