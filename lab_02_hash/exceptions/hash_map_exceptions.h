#pragma once

#include "base_exception.h"

class MemoryError : public BaseContainerError
{
public:
    MemoryError(const char *filename,
                const char *classname,
                int line,
                const char *time,
                const char *message = "Memory allocation error!")
        : BaseContainerError(filename, classname, line, time, message) {};
};

class BadCapacityError : public BaseContainerError
{
public:
    BadCapacityError(const char *filename,
                     const char *classname,
                     int line,
                     const char *time,
                     const char *message = "Capacity passed is less than one!")
        : BaseContainerError(filename, classname, line, time, message) {};
};

class TableIndexOutOfRange : public BaseError
{
public:
    TableIndexOutOfRange(const char *filename, const char *classname, int line_num, const char *message = "Requested index is out of hash table range!")
        : BaseError(filename, classname, line_num, message) {};
};

class BadCountError : public BaseContainerError
{
public:
    BadCountError(const char *filename,
                  const char *classname,
                  int line,
                  const char *time,
                  const char *message = "Error, Count less than one!")
        : BaseContainerError(filename, classname, line, time, message) {};
};

class KeyNotFoundError : public BaseContainerError
{
public:
    KeyNotFoundError(const char *filename,
                     const char *classname,
                     int line,
                     const char *time,
                     const char *message = "Requested key was not found!")
        : BaseContainerError(filename, classname, line, time, message) {};
};
