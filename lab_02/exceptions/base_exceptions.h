#pragma once

#include <exception>
#include <iostream>

#define BUF_SIZE 512

class BaseError : public std::exception
{
public:
    BaseError(const char *file_name,
              int line,
              const char *class_name, const char *time,
              const char *err_name = "Error!")
    {
        // Форматируем строку и сохраняем результат в буфере
        snprintf(err_message, sizeof(err_message), "\nInfo: %s\nFile: %s\nLine: %d\nClass: %s\nTime: %s\n", err_name, file_name, line, class_name, time);
    }

    // возвращает информацию об ошибке
    virtual const char *what() const noexcept override
    {
        return err_message;
    }

protected:
    char err_message[BUF_SIZE];
};

class BaseContainerError : public BaseError
{
public:
    BaseContainerError(const char *file_name,
                       int line,
                       const char *class_name,
                       const char *time,
                       const char *err_name = "Container error!")
        : BaseError(file_name, line, class_name, time, err_name)
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
        : BaseError(file_name, line, class_name, time, err_name)
    {
    }
};
