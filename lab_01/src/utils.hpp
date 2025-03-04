#ifndef UTILS_HPP__
#define UTILS_HPP__

#include <QString>
#include "errors.hpp"

const char *convert_QString_to_char(const QString &);

err_t read_int_number(FILE *, size_t &);
#endif // UTILS_HPP__