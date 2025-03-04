#ifndef UTILS_HPP__
#define UTILS_HPP__

#include <QString>

const char *convert_QString_to_char(const QString &);

err_t read_int_number(FILE *, int &);
#endif // UTILS_HPP__