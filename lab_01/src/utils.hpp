#ifndef UTILS_HPP__
#define UTILS_HPP__

#include <QString>
#include "errors.hpp"

const char *convert_QString_to_char(const QString &);

err_t read_int_number(size_t &, FILE *);
err_t read_elements_count(size_t &, FILE *);
#endif // UTILS_HPP__