#pragma once

#include "vector.h"
#include "vector_exceptions.h"
#include "vector_iterator.h"

#include <iostream>
#include <memory>

template <ContainerType T>
Vector<T>::Vector()
{
    len = 0;
    memory_allocation(len, __LINE__);
}

template <ContainerType T>
Vector<T>::Vector(const Vector<T> &other)
{
    len = other.size();
    memory_allocation(len, __LINE__);

    VectorIterator<T> iter = this->begin();

    for (auto iter1 = other.cbegin(); iter1 != other.cend(); iter1++)
    {
        *iter = *iter1;
        iter++;
    }

}

// template <ContainerType T>
// {

// }

template <ContainerType T>
void Vector<T>::memory_allocation(const size_t &size, int line)
{
    try
    {
        container.reset(new T[size], std::default_delete<T[]>());
    }
    catch (std::bad_alloc &exc)
    {
        time_t now = time(NULL);
        throw errMemory(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}
