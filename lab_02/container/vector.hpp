#pragma once

#include "vector.h"
#include "vector_const_iterator.h"
#include "vector_exceptions.h"
#include "vector_iterator.h"

#include "constants.hpp"

#include <iostream>
#include <math.h>
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
    this->container_size = other.size();
    this->container = other.container;
    other.container.reset();
}

template <ContainerType T>
template <ConvertAssignable<T> T1>
Vector<T>::Vector(const Vector<T1> &other)
{
    this->container_size = other.size();
    this->memory_allocation(this->container_size, __LINE__);

    VectorIterator<T> iter = this->begin();
    for (auto iter1 = other.cbegin(); iter1 != other.cend(); iter1++)
    {
        *iter = *iter1;
        iter++;
    }
}

template <ContainerType T>
template <typename Con>
    requires ValidContainer<T, Con>
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
decltype(auto) Vector<T>::len() const
{
    this->check_vector_size(this->container_size, __LINE__);

    T sum = 0;
    VectorIterator iter = this->begin();
    for (; iter != this->end(); iter++)
    {
        sum += *iter * *iter;
    }

    return std::sqrt(sum);
}

/**
 * @brief Функция нормализует вектор, тоесть приводит его к единичному
 */
template <ContainerType T>
decltype(auto) Vector<T>::normalization(void) const
{
    this->check_vector_size(this->container_size, __LINE__); // Проверяем размер вектора

    auto vector_len = this->len(); // Узнаем математическую длину вектора
    this->check_division_zero(vector_len, __LINE__);

    Vector<decltype((*this)[0] / vector_len)> res_vector(*this);
    res_vector /= vector_len;
    return res_vector;
}

template <ContainerType T>
VectorIterator<T> Vector<T>::begin(void) const noexcept
{
    VectorIterator<T> iter(*this);
    return iter;
}

// возвращает мой итератор на конец вектора
template <ContainerType T>
VectorIterator<T> Vector<T>::end(void) const noexcept
{
    VectorIterator<T> iter(*this);
    return iter + container_size;
}

// возвращает мой константный итератор на начало вектора
template <ContainerType T>
VectorConstIterator<T> Vector<T>::cbegin(void) const noexcept
{
    VectorConstIterator<T> iter(*this);
    return iter;
}

// возвращает мой константный итератор на конец вектора
template <ContainerType T>
VectorConstIterator<T> Vector<T>::cend(void) const noexcept
{
    VectorConstIterator<T> iter(*this);
    return iter + container_size;
}

// Получить элемент по индексу
template <ContainerType T>
T &Vector<T>::get_item(int ind)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_index(ind, __LINE__);
    VectorIterator<T> iter = this->begin();
    for (int i = 0; i < ind; i++)
        iter++;
    return *iter;
}

template <ContainerType T>
const T &Vector<T>::get_item(int ind) const
{
    this->check_vector_size(this->count_axis, __LINE__);
    this->check_index(ind, __LINE__);
    VectorIterator<T> iter = this->cbegin();
    for (int i = 0; i < ind; i++)
        iter++;
    return *iter;
}

// Перегрузка оператора []
template <ContainerType T>
T &Vector<T>::operator[](int ind)
{
    return get_item(ind);
}

// Перегрузка оператора []
template <ContainerType T>
const T &Vector<T>::operator[](int ind) const
{
    return get_item(ind);
}

// Перегрузка оператора ==
template <ContainerType T>
template <typename Con>
    requires ValidContainer<T, Con>
bool Vector<T>::operator==(const Con &other) const
{
    bool rc = this->container_size == other.size();

    if (rc)
    {
        VectorIterator<T> iter = this->begin();

        for (auto iter1 = other.begin(); iter1 != other.end() && rc; iter++)
        {
            if (std::fabs(*iter - *iter1) > EPS)
                rc = false;

            iter++;
        }
    }

    return rc;
}

// Перегрузка оператора !=
template <ContainerType T>
template <typename Con>
    requires ValidContainer<T, Con>
bool Vector<T>::operator!=(const Con &other) const
{
    return !(*this == other);
}

// Метод
template <ContainerType T>
template <typename Con>
    requires ValidContainer<T, Con>
bool Vector<T>::is_equal(const Con &other) const
{
    return *this == other;
}

// Перегрузка оператора /
template <ContainerType T>
template <ConvertAssignableDiv<T> T1>
decltype(auto) Vector<T>::operator/(const T1 &num) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_division_zero(num, __LINE__);

    Vector<decltype((*this)[0] / num)> res_vector(*this);
    VectorIterator<T> iter = res_vector.begin();
    for (; iter != res_vector.end(); iter++)
        *iter /= num;
    return res_vector;
}

// Перегрузка оператора /=
template <ContainerType T>
template <ConvertAssignableDiv<T> T1>
Vector<T> &Vector<T>::operator/=(const T1 &num)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_division_zero(num, __LINE__);

    *this /= num;
    // *this = (Vector<T>)(*this / num);
    return *this;
}

// перегрузка оператора равно
template <ContainerType T>
template <Convertiable<T> U>
Vector<T> &Vector<T>::operator=(const std::initializer_list<U> &arr)
{
    this->container_size = arr.size();
    this->memory_allocation(this->container_size, __LINE__);

    VectorIterator<T> iter = this->begin();
    for (const auto &elem : arr)
    {
        *iter = static_cast<T>(elem);
        iter++;
    }

    return *this;
}

// перегрузка оператора равно
template <ContainerType T>
template <Convertiable<T> U>
Vector<T> &Vector<T>::operator=(const Vector<U> &other)
{
    this->container_size = other.size();
    this->memory_allocation(this->container_size, __LINE__);
    VectorIterator<T> iter = this->begin();
    for (auto iter1 = other.begin(); iter1 != other.end(); iter1++)
    {
        *iter = *iter1;
        iter++;
    }
    return *this;
}

// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// |                          Приватные функции                                |
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

template <ContainerType T>
void Vector<T>::memory_allocation(const int &container_size, int line)
{
    try
    {
        container.reset(new T[container_size], std::default_delete<T[]>());
    }
    catch (std::bad_alloc &exc)
    {
        throw errMemory(__FILE__, line, typeid(*this).name());
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
        throw errNegSize(__FILE__, line, typeid(*this).name());
    }
}

template <ContainerType T>
void Vector<T>::check_arr_null(const T *arr, int line) const
{
    if (arr == NULL)
    {
        throw errArrNull(__FILE__, line, typeid(*this).name());
    }
}

template <ContainerType T>
template <typename U>
void Vector<T>::check_division_zero(const U &num, int line) const
{
    if (std::abs(num) < EPS)
    {
        throw errDivisionZero(__FILE__, line, typeid(*this).name());
    }
}

template <ContainerType T>
void Vector<T>::check_index(const int &index, int line) const
{
    if (index < 0 || index >= this->container_size)
    {
        throw errIndexOutOfRange(__FILE__, line, typeid(*this).name());
    }
}
