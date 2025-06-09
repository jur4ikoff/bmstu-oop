#ifndef HASHERROR_H
#define HASHERROR_H
#include <exception>
#include <cstdio>

class BaseError: public std::exception
{
private:
    char err_msg[500];
public:
    BaseError(const char *filename, const char *classname, int line_num, const char *message = "Oops! Error!") {
        snprintf(err_msg, sizeof(err_msg), "%s\nFilename: %s\nClass: %s\nLine: %d\n",
                 message, filename, classname, line_num);
    }
    virtual const char *what() const noexcept override {
        return err_msg;
    }
};

class MemoryError: public BaseError
{
public:
    MemoryError(const char *filename, const char *classname, int line_num, const char *message = "Malloc error!"):
        BaseError(filename, classname, line_num, message) {};
};

class BadCapacityError: public BaseError
{
public:
    BadCapacityError(const char *filename, const char *classname, int line_num, const char *message = "Capacity passed is less than one!"):
        BaseError(filename, classname, line_num, message) {};
};

class KeyNotFoundError: public BaseError
{
public:
    KeyNotFoundError(const char *filename, const char *classname, int line_num, const char *message = "Requested key was not found!"):
        BaseError(filename, classname, line_num, message) {};
};

class TableIndexOutOfRange: public BaseError
{
public:
    TableIndexOutOfRange(const char *filename, const char *classname, int line_num, const char *message = "Requested index is out of hash table range!"):
        BaseError(filename, classname, line_num, message) {};
};

// Итераторы

class IteratorTableWasChanged: public BaseError
{
public:
    IteratorTableWasChanged(const char *filename, const char *classname, int line_num, const char *message = "Iterator is not valid (hash table was changed)!"):
        BaseError(filename, classname, line_num, message) {};
};

class IteratorNoDataFound: public BaseError
{
public:
    IteratorNoDataFound(const char *filename, const char *classname, int line_num, const char *message = "Iterator is not valid (hash table was changed)!"):
        BaseError(filename, classname, line_num, message) {};
};

class IteratorDoesntExistError: public BaseError
{
public:
    IteratorDoesntExistError(const char *filename, const char *classname, int line_num, const char *message = "Iterator is linked to a hash table that doesn't exist!"):
        BaseError(filename, classname, line_num, message) {};
};

#endif // HASHERROR_H
