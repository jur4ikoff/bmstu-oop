#pragma once

#include "vector.h"
#include "vector_const_iterator.h"
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
        *iter = static_cast<T>(*iter1);
        iter++;
    }
}

template <ContainerType T>
Vector<T>::Vector(Vector<T> &&other) noexcept
{
    this->len = other.len;
    this->container = other.container;
    other.container.reset();
}

template <ContainerType T>
template <ConvertAssignable<T> T1>
Vector<T>::Vector(const Vector<T1> &other)
{
    this->len = other.len;
    this->memory_allocation(this->len, __LINE__);

    VectorIterator<T> iter = this->begin();
    for (auto iter1 = other.cbegin(); iter1 != other.cend(); iter1++)
    {
        *iter = *iter1;
        iter++;
    }
}

template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T>::Vector(const Con &other)
{
    len = other.len;
    this->memory_allocation(this->len, __LINE__);

    VectorIterator<T> iter = this->begin();
    for (auto iter1 = other.cbegin(); iter1 != other.cend(); iter1++)
    {
        *iter = *iter1;
        iter++;
    }
}

template <ContainerType T>
Vector<T>::Vector(const int &size)
{
    this->check_vector_size(size, __LINE__);
    this->len = size;
    this->memory_allocation(size, __LINE__);
}

template <ContainerType T>
// template <Convertiable <T> T1>
// Убрал концепт, потому что он мешает билду,
// при случаях, когда в списке данные разных типов
Vector<T>::Vector(std::initializer_list<T> arr)
{
    this->len = arr.size();
    this->memory_allocation(len, __LINE__);

    VectorIterator<T> iter = this->begin();

    for (auto elem : arr)
    {
        *iter = elem;
        iter++;
    }
}

// template <ContainerType T>
// template <typename... Args>
//     requires(std::convertible_to<Args, T> && ...)
// Vector<T>::Vector(Args &&...args) : len(sizeof...(Args))
// {
//     memory_allocation(len, __LINE__);
//     T *data = begin();
//     ((*data++ = static_cast<T>(args)), ...); // Распаковка аргументов
// }

template <ContainerType T>
VectorIterator<T> Vector<T>::begin(void) noexcept
{
    VectorIterator<T> iter(*this);
    return iter;
}

// возвращает мой итератор на конец вектора
template <ContainerType T>
VectorIterator<T> Vector<T>::end(void) noexcept
{
    VectorIterator<T> iter(*this);
    return iter + len;
}

// возвращает мой константный итератор на начало вектора
template <ContainerType T>
VectorConstIterator<T> Vector<T>::cbegin(void) const noexcept
{
    VectorConstIterator<T> iter(*this);
    // VectorConstIterator<T> iter(); Ошибка компиляции
    return iter;
}

// возвращает мой константный итератор на конец вектора
template <ContainerType T>
VectorConstIterator<T> Vector<T>::cend(void) const noexcept
{
    VectorConstIterator<T> iter(*this);
    return iter + len;
}

template <ContainerType T>
void Vector<T>::memory_allocation(const int &size, int line)
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

template <ContainerType T>
void Vector<T>::check_vector_size(const int &size, int line)
{
    if (size <= 0)
    {
        time_t now = time(NULL);
        throw errNegSize(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}
