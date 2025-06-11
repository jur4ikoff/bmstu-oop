#pragma once

#include <exception>
#include <iostream>

#define BUF_SIZE 512

class BaseError : public std::exception
{
public:
    BaseError(const char *filename, const char *class_name, int line, const char *time, const char *err_name = "Error!")
    {
        snprintf(_err_message, sizeof(_err_message), "%s\nFilename: %s\nClass: %s\nLine: %d Time: %s\n",
                 err_name, filename, class_name, line, time);
    }
    virtual const char *what() const noexcept override
    {
        return _err_message;
    }

protected:
    char _err_message[BUF_SIZE];
};

class BaseContainerError : public BaseError
{
public:
    BaseContainerError(const char *filename,
                       const char *class_name,
                       int line,
                       const char *time,
                       const char *err_name = "Container error!")
        : BaseError(filename, class_name, line, time, err_name)
    {
    }
};

class BaseHashChainError : public BaseError
{
public:
    BaseHashChainError(const char *filename,
                       const char *class_name,
                       int line,
                       const char *time,
                       const char *err_name = "Hash Chain error!")
        : BaseError(filename, class_name, line, time, err_name)
    {
    }
};

class BaseIteratorError : public BaseError
{
    BaseIteratorError(const char *file_name,
                      int line,
                      const char *class_name,
                      const char *time,
                      const char *err_name = "Iterator error!")
        : BaseError(file_name, class_name, line, time, err_name)
    {
    }
};
