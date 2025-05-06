#pragma once

#include "vector.h"
#include "vector_const_iterator.h"
#include "vector_exceptions.h"
#include "vector_iterator.h"

#include "constants.hpp"

#include <iostream>
#include <memory>
#include <stdarg.h>

// ------------------------------------------------------------------
// |                     Конструкторы
// ------------------------------------------------------------------

template <ContainerType T>
Vector<T>::Vector()
{
    container_size = 0;
    memory_allocation(container_size, __LINE__);
}

template <ContainerType T>
Vector<T>::Vector(const Vector<T> &other)
{
    container_size = other.size();
    memory_allocation(container_size, __LINE__);

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
    this->container_size = other.container_size;
    this->container = other.container;
    other.container.reset();
}

template <ContainerType T>
template <ConvertAssignable<T> T1>
Vector<T>::Vector(const Vector<T1> &other)
{
    this->container_size = other.container_size;
    this->memory_allocation(this->container_size, __LINE__);

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
    container_size = other.container_size;
    this->memory_allocation(this->container_size, __LINE__);

    VectorIterator<T> iter = this->begin();
    for (auto iter1 = other.cbegin(); iter1 != other.cend(); iter1++)
    {
        *iter = *iter1;
        iter++;
    }
}

template <ContainerType T>
Vector<T>::Vector(const int &container_size)
{
    this->check_vector_size(container_size, __LINE__);
    this->container_size = container_size;
    this->memory_allocation(container_size, __LINE__);
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>::Vector(std::initializer_list<U> arr)
{
    this->container_size = arr.size();
    this->memory_allocation(container_size, __LINE__);

    VectorIterator<T> iter = this->begin();

    for (auto elem : arr)
    {
        *iter = elem;
        iter++;
    }
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>::Vector(int container_size, const U *arr)
{
    this->check_vector_size(container_size, __LINE__);
    this->check_arr_null(arr, __LINE__);

    this->container_size = container_size;
    this->memory_allocation(this->container_size, __LINE__);

    VectorIterator<T> iter = this->begin();

    for (int i = 0; i < container_size; i++)
    {
        *iter = arr[i];
        iter++;
    }
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>::Vector(int container_size, U elem, ...)
{
    this->check_vector_size(container_size, __LINE__);
    this->container_size = container_size;

    this->memory_allocation(container_size, __LINE__);
    VectorIterator<T> iter = this->begin();

    va_list args;
    va_start(args, elem);

    for (int i = 0; i < container_size; i++)
    {
        *iter = elem;
        elem = va_arg(args, U);
        iter++;
    }
}

template <ContainerType T>
template <ForwardIterator U>
Vector<T>::Vector(U begin, U end)
{
    // Вычисляем размер
    int container_size = end - begin;
    this->check_vector_size(container_size, __LINE__);
    this->container_size = container_size;

    this->memory_allocation(container_size, __LINE__);

    VectorIterator<T> iter = this->begin();
    VectorIterator<T> test = this->begin();
    for (auto iter1 = begin; iter1 != end; iter1++)
    {
        *iter = *iter1;
        iter++;
    }
}

// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// |                   Функции для работы с вектором                               |
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

template <ContainerType T>
decltype(auto) Vector<T>::len()
{
    this->check_vector_size(this->container_size, __LINE__);
    return 0;
}

/**
 * @brief Функция нормализует вектор, тоесть приводит его к единичному
 */
template <ContainerType T>
decltype(auto) Vector<T>::normalization(void) const
{
    this->check_vector_size(this->container_size, __LINE__); // Проверяем размер вектора

    auto len = this->len(); // Узнаем математическую длину вектора

    // try:
    this->check_division_zero(len, __LINE__);
    // catch (const errDivisionZero &e)

    Vector<decltype((*this)[0] / len)> res_vector(*this);
    res_vector /= len;
}

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
    return iter + container_size;
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
    return iter + container_size;
}

template <ContainerType T>
void Vector<T>::memory_allocation(const int &container_size, int line)
{
    try
    {
        container.reset(new T[container_size], std::default_delete<T[]>());
    }
    catch (std::bad_alloc &exc)
    {
        time_t now = time(NULL);
        throw errMemory(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}

// --------------------------------------------------------------------
// Проверки
// --------------------------------------------------------------------
template <ContainerType T>
void Vector<T>::check_vector_size(const int &container_size, int line) const
{
    if (container_size <= 0)
    {
        time_t now = time(NULL);
        throw errNegSize(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}

template <ContainerType T>
void Vector<T>::check_arr_null(const T *arr, int line) const
{
    if (arr == NULL)
    {
        time_t now = time(NULL);
        throw errArrNull(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}

template <ContainerType T>
template <typename U>
void Vector<T>::check_division_zero(const U &num, int line) const
{
    if (std::abs(num) < EPS)
    {
        time_t now = time(NULL);
        throw errDivisionZero(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}
