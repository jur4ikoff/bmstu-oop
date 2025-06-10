#pragma once

#include <iostream>

class BaseHashMap
{
public:
    virtual ~BaseHashMap() = default;
    virtual size_t size() const = 0;
    virtual bool empty() const = 0;
    virtual size_t get_capacity() const = 0;
    virtual size_t get_count() const = 0;

protected:
    size_t _capacity;
};
