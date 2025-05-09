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

// ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// |                     Конструкторы                               |
// ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

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
template <typename U>
    requires ConvertAssignable<T, U>
Vector<T>::Vector(const Vector<U> &other)
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

// Функция проверяет нормализован ли вектор
template <ContainerType T>
bool Vector<T>::is_normalize() const
{
    this->check_vector_size(this->container_size, __LINE__); // Проверяем размер вектора

    auto vector_len = this->len();
    if (std::fabs(vector_len) < EPS)
        return false;

    return std::fabs(vector_len - 1) < EPS;
}

// Функция проверяет нулевой ли вектор
template <ContainerType T>
bool Vector<T>::is_zero() const
{
    this->check_vector_size(this->container_size, __LINE__); // Проверяем размер вектора

    auto vector_len = this->len();
    return std::fabs(vector_len) < EPS;
}

// Функция считает угол между двумя векторами
template <ContainerType T>
template <ConvertAssignable<T> U>
decltype(auto) Vector<T>::calc_angle(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    auto mul_len = this->len() * other.len();
    this->check_division_zero(mul_len, __LINE__);

    auto angle = (*this & other) / mul_len;
    auto res = std::acos(angle);
    return res * 180 / M_PI;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
bool Vector<T>::is_colliniar(const Vector<U> &other) const
{
    return fabs(this->calc_angle(other)) < EPS;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
bool Vector<T>::is_orthogonal(const Vector<U> &other) const
{
    return fabs(this->calc_angle(other) - 90) < EPS;
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

// Установить значение элемента по индексу
template <ContainerType T>
template <ConvertAssignable<T> U>
void Vector<T>::set_item(size_type index, const U &elem)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_index(index, __LINE__);
    this->get_item(index) = elem;
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

// Перегрузка оператора +
// Сложение вектора с другим вектором
// Возвращается новый объект Vector<auto>
template <ContainerType T>
template <ConvertAssignableSum<T> U>
decltype(auto) Vector<T>::operator+(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    Vector<decltype(((*this)[0]) + other[0])> result(*this);

    VectorIterator<decltype(((*this)[0]) + other[0])> iter = result.begin();
    for (VectorIterator iter1 = other.begin(); iter1 != other.end(); iter1++, iter++)
    {
        *iter += *iter1;
    }

    return result;
}

// Перегрузка оператора +=
// Сложение вектора с другим вектором
// Изменяется текущий объект
template <ContainerType T>
template <ConvertAssignableSum<T> U>
Vector<T> &Vector<T>::operator+=(const Vector<U> &other)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    VectorIterator<T> iter = this->begin();
    for (VectorIterator iter1 = other.begin(); iter1 != other.end(); iter1++, iter++)
    {
        *iter += *iter1;
    }
    return *this;
}

/// @brief  Перегрузка оператора + для сложение вектора с числом
/// @tparam T
/// @param Число для сложение
/// @return
template <ContainerType T>
template <ConvertAssignableSum<T> U>
decltype(auto) Vector<T>::operator+(const U &num) const
{
    this->check_vector_size(this->container_size, __LINE__);

    Vector<decltype(((*this)[0]) + num)> result(*this);

    for (auto iter = result.begin(); iter != result.end(); iter++)
    {
        *iter += num;
    }

    return result;
}

/// @brief  Перегрузка оператора += для сложение вектора с числом
/// @tparam T
/// @param Число для сложение
/// @return
template <ContainerType T>
template <ConvertAssignableSum<T> U>
Vector<T> &Vector<T>::operator+=(const U &num)
{
    this->check_vector_size(this->container_size, __LINE__);

    for (auto iter = (*this).begin(); iter != (*this).end(); iter++)
    {
        *iter += num;
    }

    return *this;
}

/// @brief Перегрузка оператора - для Вектора. Функция вычитает один вектор из другого
/// @tparam T
/// @param other
/// @return
template <ContainerType T>
template <ConvertAssignableSub<T> U>
decltype(auto) Vector<T>::operator-(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    Vector<decltype((*this)[0] - other[0])> result(*this);
    VectorIterator<decltype((*this)[0] - other[0])> iter = result.begin();

    for (auto iter1 = other.begin(); iter1 != other.end(); iter1++, iter++)
    {
        *iter -= *iter1;
    }

    return result;
}

template <ContainerType T>
template <ConvertAssignableSub<T> U>
Vector<T> &Vector<T>::operator-=(const Vector<U> &other)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    VectorIterator<T> iter = (*this).begin();

    for (auto iter1 = other.begin(); iter1 != other.end(); iter1++, iter++)
    {
        *iter -= *iter1;
    }

    return *this;
}

// Перегрзука оператора - для числа
template <ContainerType T>
template <ConvertAssignableSub<T> U>
decltype(auto) Vector<T>::operator-(const U &num) const
{
    this->check_vector_size(this->container_size, __LINE__);

    Vector<decltype((*this)[0] - num)> result(*this);

    for (auto iter = result.begin(); iter != result.end(); iter++)
    {
        *iter -= num;
    }

    return result;
}

template <ContainerType T>
template <ConvertAssignableSub<T> U>
Vector<T> &Vector<T>::operator-=(const U &num)
{
    this->check_vector_size(this->container_size, __LINE__);

    for (auto iter = (*this).begin(); iter != (*this).end(); iter++)
    {
        *iter -= num;
    }

    return *this;
}

// Перегрузка *
// Перегрузка оператора умножения для вектора
template <ContainerType T>
template <ConvertAssignableMul<T> U>
decltype(auto) Vector<T>::operator*(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    Vector<decltype((*this)[0] - other[0])> result(*this);
    VectorIterator<decltype((*this)[0] - other[0])> iter = result.begin();

    for (auto iter1 = other.begin(); iter1 != other.end(); iter1++, iter++)
    {
        *iter *= *iter1;
    }

    return result;
}

template <ContainerType T>
template <ConvertAssignableMul<T> U>
Vector<T> &Vector<T>::operator*=(const Vector<U> &other)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    VectorIterator<T> iter = (*this).begin();

    for (auto iter1 = other.begin(); iter1 != other.end(); iter1++, iter++)
    {
        *iter *= *iter1;
    }

    return *this;
}

// Перегрзука оператора * для числа
template <ContainerType T>
template <ConvertAssignableMul<T> U>
decltype(auto) Vector<T>::operator*(const U &num) const
{
    this->check_vector_size(this->container_size, __LINE__);

    Vector<decltype((*this)[0] - num)> result(*this);

    for (auto iter = result.begin(); iter != result.end(); iter++)
    {
        *iter *= num;
    }

    return result;
}

template <ContainerType T>
template <ConvertAssignableMul<T> U>
Vector<T> &Vector<T>::operator*=(const U &num)
{
    this->check_vector_size(this->container_size, __LINE__);

    for (auto iter = (*this).begin(); iter != (*this).end(); iter++)
    {
        *iter *= num;
    }

    return *this;
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

    VectorIterator<T> iter = this->begin();
    for (; iter != this->end(); iter++)
    {
        *iter = *iter / num;
    }
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
        *iter = elem;
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

// Скалярное произведение векторов
template <ContainerType T>
template <Convertiable<T> U>
decltype(auto) Vector<T>::operator&(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    decltype((*this)[0] * other[0]) sum = 0;

    auto iter1 = other.begin();

    for (VectorIterator<T> iter = this->begin(); iter != this->end(); iter++, iter1++)
    {
        sum += (*iter * *iter1);
    }

    return sum;
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

// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// | Приватные функции, проверяющие входные параметры. Выбрасывают исключения  |
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
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

/// @brief Функция проверяет эквивалентность размера текущего объекта и введенного значения
/// @tparam T type
/// @param size Размер второго вектора/ значение, с которым нужно сравнить
/// @param line Номер строки, нужен для сообщение об ошибке
template <ContainerType T>
void Vector<T>::check_size_equal(const size_type &size, int line) const
{
    this->check_vector_size(this->container_size, __LINE__);
    if (std::fabs(this->container_size - size) > EPS)
    {
        throw errVectorsSizeNotEqual(__FILE__, line, typeid(*this).name());
    }
}
