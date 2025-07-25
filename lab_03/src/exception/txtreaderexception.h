#pragma once
#include "baseexception.h"

class TxtReaderException : public BaseException
{
public:
    TxtReaderException(const char *time, const char *filename,
                       const size_t line, const char *class_name,
                       const char *method_name,
                       const char *info = "Txt reader exception.")
        : BaseException(time, filename, line, class_name, method_name, info) {};
};

class TxtNoFileException : public TxtReaderException
{
public:
    TxtNoFileException(const char *time, const char *filename,
                       const size_t line, const char *class_name,
                       const char *method_name,
                       const char *info = "Can't open txt file exception.")
        : TxtReaderException(time, filename, line, class_name, method_name, info) {};
};

class TxtReadException : public TxtReaderException
{
public:
    TxtReadException(const char *time, const char *filename,
                     const size_t line, const char *class_name,
                     const char *method_name,
                     const char *info = "Can't read from txt file exception.")
        : TxtReaderException(time, filename, line, class_name, method_name, info) {};
};
