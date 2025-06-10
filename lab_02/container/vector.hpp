#pragma once

#include "vector.h"
#include "vector_const_iterator.h"
#include "vector_const_reverse_iterator.h"
#include "vector_exceptions.h"
#include "vector_iterator.h"

#include "constants.hpp"

#include <ctime>
#include <ranges>
#include <iostream>
#include <math.h>
#include <memory>
#include <numeric>
#include <stdarg.h>

// ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// |                     Конструкторы                               |
// ––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

template <ContainerType T>
Vector<T>::Vector()
{
    container_size = 0;
    this->memory_allocation(container_size, __LINE__);
}

template <ContainerType T>
Vector<T>::Vector(const Vector<T> &other)
{
    container_size = other.size();
    memory_allocation(container_size, __LINE__);
    std::copy(other.cbegin(), other.cend(), this->begin());
}

template <ContainerType T>
Vector<T>::Vector(Vector<T> &&other) noexcept
{
    this->container_size = other.container_size;
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
    std::copy(other.cbegin(), other.cend(), this->begin());
}

template <ContainerType T>
template <typename Con>
    requires ValidContainer<T, Con>
Vector<T>::Vector(const Con &other)
{
    this->container_size = other.container_size;
    this->memory_allocation(this->container_size, __LINE__);
    std::copy(other.cbegin(), other.cend(), this->begin());
}

template <ContainerType T>
Vector<T>::Vector(baseContainer::size_type size)
{
    this->check_vector_size(size, __LINE__);
    this->container_size = size;
    this->memory_allocation(size, __LINE__);
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>::Vector(std::initializer_list<U> arr)
{
    this->container_size = arr.size();
    this->memory_allocation(this->container_size, __LINE__);
    std::copy(arr.begin(), arr.end(), this->begin());
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>::Vector(baseContainer::size_type size, const U *arr)
{
    this->check_vector_size(size, __LINE__);
    this->check_arr_null(arr, __LINE__);
    this->container_size = size;
    this->memory_allocation(this->container_size, __LINE__);
    std::copy(arr, arr + size, this->begin());
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T>::Vector(baseContainer::size_type size, const U &elem, ...)
{
    this->check_vector_size(size, __LINE__);
    this->container_size = size;
    this->memory_allocation(size, __LINE__);

    auto iter = this->begin();
    *iter = elem;

    va_list args;
    va_start(args, elem);
    fill_elements_va(++iter, size - 1, args);
    va_end(args);
}

template <ContainerType T>
template <CompatibleIterator<T> U>
Vector<T>::Vector(U begin, U end)
{
    // Вычисляем размер
    int size = end - begin;
    this->check_vector_size(size, __LINE__);
    this->container_size = size;
    this->memory_allocation(size, __LINE__);
    std::copy(begin, end, this->begin());
}

template <ContainerType T>
template <typename I, typename S>
    requires CompatibleIterator<I, T> && SentinelIter<S, I>
Vector<T>::Vector(I begin, S end)
{
    auto size = std::ranges::distance(begin, end);
    this->container_size = size;
    this->memory_allocation(size, __LINE__);

    std::copy(begin, end, this->begin());
}

// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// |                  Математические Функции для работы с вектором                 |
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

template <ContainerType T>
decltype(auto) Vector<T>::len() const
{
    this->check_vector_size(this->container_size, __LINE__);
    // a | b     Применить b к a
    auto squared_view = *this | std::views::transform([](const T &x)
                                                      { return x * x; });
    const T sum = std::accumulate(squared_view.begin(), squared_view.end(), T{0});
    return std::sqrt(sum);
}

/// @brief Функция нормализует вектор, тоесть приводит его к единичному
/// @tparam T
/// @return Новый объект - нормализованный вектор
template <ContainerType T>
decltype(auto) Vector<T>::normalization() const
{
    this->check_vector_size(this->container_size, __LINE__);
    auto vector_len = this->len();
    this->check_division_zero(vector_len, __LINE__);

    Vector<decltype((*this)[0] / vector_len)> res_vector(*this);
    res_vector /= vector_len;
    return res_vector;
}

/// @brief Функция проверяет нормализован ли вектор
/// @tparam T
/// @return true если нормализовано, false если нет
template <ContainerType T>
bool Vector<T>::is_normalize() const
{
    this->check_vector_size(this->container_size, __LINE__);
    auto vector_len = this->len();
    return std::fabs(vector_len - 1) < EPS;
}

// Функция проверяет нулевой ли вектор
template <ContainerType T>
bool Vector<T>::is_zero() const
{
    this->check_vector_size(this->container_size, __LINE__);

    auto vector_len = this->len();
    return std::fabs(vector_len) < EPS;
}

/// @brief Ищет угол между двумя векторами
/// @tparam T
/// @param other Второй вектор
/// @return Угол в градусах
template <ContainerType T>
template <ConvertAssignable<T> U>
decltype(auto) Vector<T>::calc_angle(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    auto mul_len = this->len() * other.len();
    this->check_division_zero(mul_len, __LINE__);

    // Скалярное произведение поделить на произведение длинн
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

// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// |                            Геттеры и сеттеры                              |
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

// Установить значение элемента по индексу
template <ContainerType T>
template <ConvertAssignable<T> U>
void Vector<T>::set_item(int index, const U &elem)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_index(index, __LINE__);
    this->get_item(index) = elem;
}

// Получить элемент по индексу
template <ContainerType T>
typename Vector<T>::reference Vector<T>::get_item(int index)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_index(index, __LINE__);
    return *std::ranges::next(this->begin(), index);
}

template <ContainerType T>
typename Vector<T>::const_reference Vector<T>::get_item(int index) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_index(index, __LINE__);
    return *std::ranges::next(this->cbegin(), index);
}

// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// |                                Итераторы                                  |
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

template <ContainerType T>
VectorIterator<T> Vector<T>::begin(void)
{
    VectorIterator<T> iter(*this);
    return iter;
}

// возвращает мой итератор на конец вектора
template <ContainerType T>
VectorIterator<T> Vector<T>::end(void)
{
    VectorIterator<T> iter(*this);
    return iter + container_size;
}

template <ContainerType T>
VectorConstIterator<T> Vector<T>::begin(void) const
{
    VectorConstIterator<T> iter(*this);
    return iter;
}

// возвращает мой итератор на конец вектора
template <ContainerType T>
VectorConstIterator<T> Vector<T>::end(void) const
{
    VectorConstIterator<T> iter(*this);
    return iter + container_size;
}

// возвращает мой константный итератор на начало вектора
template <ContainerType T>
VectorConstIterator<T> Vector<T>::cbegin(void) const
{
    VectorConstIterator<T> iter(*this);
    return iter;
}

// возвращает мой константный итератор на конец вектора
template <ContainerType T>
VectorConstIterator<T> Vector<T>::cend(void) const
{
    VectorConstIterator<T> iter(*this);
    return iter + this->container_size;
}

template <ContainerType T>
VectorReverseIterator<T> Vector<T>::rbegin(void)
{
    VectorReverseIterator<T> iter(*this);
    return iter;
}

template <ContainerType T>
VectorReverseIterator<T> Vector<T>::rend(void)
{
    VectorReverseIterator<T> iter(*this);
    return iter + this->container_size;
}

template <ContainerType T>
VectorConstReverseIterator<T> Vector<T>::rbegin(void) const
{
    VectorConstReverseIterator<T> iter(*this);
    return iter;
}

template <ContainerType T>
VectorConstReverseIterator<T> Vector<T>::rend(void) const
{
    VectorConstReverseIterator<T> iter(*this);
    return iter + this->container_size;
}

template <ContainerType T>
VectorConstReverseIterator<T> Vector<T>::crbegin(void) const
{
    VectorConstReverseIterator<T> iter(*this);
    return iter;
}

template <ContainerType T>
VectorConstReverseIterator<T> Vector<T>::crend(void) const
{
    VectorConstReverseIterator<T> iter(*this);
    return iter + this->container_size;
}

// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// |                          Перегрузка операторов                            |
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

// Перегрузка оператора +
// Сложение вектора с другим вектором
// Возвращается новый объект Vector<auto>
template <ContainerType T>
template <ValidContainer<T> Con>
decltype(auto) Vector<T>::operator+(const Con &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    Vector<decltype(((*this)[0]) + other[0])> result(*this);

    std::ranges::transform(
        other, result,
        result.begin(), // куда записывать
        [](const auto &a, const auto &b)
        { return b + a; });

    return result;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T> &Vector<T>::operator+=(std::initializer_list<U> arr)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(arr.size(), __LINE__);
    this->check_size_equal(arr.size(), __LINE__);

    std::ranges::transform(
        *this, arr,
        this->begin(),
        [](const T &a, const U &b)
        { return a + b; });
    return *this;
}

// Перегрузка оператора +=
// Сложение вектора с другим вектором
// Изменяется текущий объект
template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::operator+=(const Con &other)
{
    *this = static_cast<Vector<T>>(*this + other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignableSum<T> U>
decltype(auto) Vector<T>::operator+(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    using ResultType = decltype((*this)[0] + other[0]);
    Vector<ResultType> result(*this);

    std::ranges::transform(
        other, result,
        result.begin(),
        [](const ResultType &a, const U &b)
        { return a + b; });

    return result;
}

template <ContainerType T>
template <ConvertAssignableSum<T> U>
Vector<T> &Vector<T>::operator+=(const Vector<U> &other)
{
    *this = static_cast<Vector<T>>(*this + other);
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

    using ResultType = decltype((*this)[0] + num);
    Vector<ResultType> result(*this);

    std::ranges::transform(
        *this,
        result.begin(),
        [&num](const U &value)
        { return value + num; });

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
    *this = static_cast<Vector<T>>(*this + num);
    return *this;
}

/// @brief Перегрузка оператора - для Вектора. Функция вычитает один вектор из другого
/// @tparam T
/// @param other
/// @return
template <ContainerType T>
template <ValidContainer<T> Con>
decltype(auto) Vector<T>::operator-(const Con &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    using ResultType = decltype((*this)[0] - other[0]);
    Vector<ResultType> result(*this);

    std::ranges::transform(
        other, result,
        result.begin(), // куда записывать
        [](const ResultType &a, const ResultType &b)
        { return b - a; });

    return result;
}

template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::operator-=(const Con &other)
{
    *this = static_cast<Vector<T>>(*this - other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignableSub<T> U>
decltype(auto) Vector<T>::operator-(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    using ResultType = decltype((*this)[0] - other[0]);
    Vector<ResultType> result(*this);

    std::ranges::transform(
        other,
        result,
        result.begin(), // куда записывать
        [](const auto &a, const auto &b)
        { return b - a; });

    return result;
}

template <ContainerType T>
template <ConvertAssignableSub<T> U>
Vector<T> &Vector<T>::operator-=(const Vector<U> &other)
{
    *this = static_cast<Vector<T>>(*this - other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T> &Vector<T>::operator-=(std::initializer_list<U> arr)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(arr.size(), __LINE__);
    this->check_size_equal(arr.size(), __LINE__);

    std::ranges::transform(
        *this, arr,
        this->begin(),
        [](const T &a, const U &b)
        { return a - b; });
    return *this;
}

// Перегрзука оператора - для числа
template <ContainerType T>
template <ConvertAssignableSub<T> U>
decltype(auto) Vector<T>::operator-(const U &num) const
{
    this->check_vector_size(this->container_size, __LINE__);

    using ResultType = decltype((*this)[0] - num);
    Vector<ResultType> result(*this);

    std::ranges::transform(*this,
                           result.begin(),
                           [&num](const U &value)
                           { return value - num; });

    return result;
}

template <ContainerType T>
template <ConvertAssignableSub<T> U>
Vector<T> &Vector<T>::operator-=(const U &num)
{
    *this = static_cast<Vector<T>>(*this - num);
    return *this;
}

// Перегрузка *
// Перегрузка оператора умножения для вектора
template <ContainerType T>
template <ValidContainer<T> Con>
decltype(auto) Vector<T>::operator*(const Con &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    using ResultType = decltype((*this)[0] * other[0]);
    Vector<ResultType> result(*this);

    std::ranges::transform(
        other, result,
        result.begin(), // куда записывать
        [](const ResultType &a, const ResultType &b)
        { return b * a; });

    return result;
}

template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::operator*=(const Con &other)
{
    *this = static_cast<Vector<T>>(*this * other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignableMul<T> U>
decltype(auto) Vector<T>::operator*(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    using ResultType = decltype((*this)[0] * other[0]);
    Vector<ResultType> result(*this);

    std::ranges::transform(
        other, result,
        result.begin(), // куда записывать
        [](const ResultType &a, const ResultType &b)
        { return b * a; });

    return result;
}

template <ContainerType T>
template <ConvertAssignableMul<T> U>
Vector<T> &Vector<T>::operator*=(const Vector<U> &other)
{
    *this = static_cast<Vector<T>>(*this * other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T> &Vector<T>::operator*=(std::initializer_list<U> arr)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(arr.size(), __LINE__);
    this->check_size_equal(arr.size(), __LINE__);

    std::ranges::transform(*this, arr,
                           this->begin,
                           [](const T &a, const U &b)
                           { return a - b; });
    return *this;
}

// Перегрзука оператора * для числа
template <ContainerType T>
template <ConvertAssignableMul<T> U>
decltype(auto) Vector<T>::operator*(const U &num) const
{
    this->check_vector_size(this->container_size, __LINE__);

    using ResultType = decltype((*this)[0] * num);
    Vector<ResultType> result(*this);

    std::ranges::transform(*this,
                           result.begin(),
                           [&num](const U &value)
                           { return value * num; });

    return result;
}

template <ContainerType T>
template <ConvertAssignableMul<T> U>
Vector<T> &Vector<T>::operator*=(const U &num)
{
    *this = static_cast<Vector<T>>(*this * num);
    return *this;
}

// ДЕЛЕНИЕ
template <ContainerType T>
template <ValidContainer<T> Con>
decltype(auto) Vector<T>::operator/(const Con &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    using ResultType = decltype((*this)[0] / other[0]);
    Vector<ResultType> result(*this);

    std::ranges::transform(
        other, result,
        result.begin(), // куда записывать
        [](const ResultType &a, const ResultType &b)
        { return b / a; });

    return result;
}

template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::operator/=(const Con &other)
{
    *this = static_cast<Vector<T>>(*this / other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignableDiv<T> U>
decltype(auto) Vector<T>::operator/(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    using ResultType = decltype((*this)[0] / other[0]);
    Vector<ResultType> result(*this);

    std::ranges::transform(
        other, result,
        result.begin(), // куда записывать
        [](const ResultType &a, const ResultType &b)
        { return b / a; });

    return result;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T> &Vector<T>::operator/=(std::initializer_list<U> arr)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(arr.size(), __LINE__);
    this->check_size_equal(arr.size(), __LINE__);

    std::ranges::transform(*this, arr, this->begin(),
                           [](const T &a, const U &b)
                           { return a / b; });
    return *this;
}

template <ContainerType T>
template <ConvertAssignableDiv<T> U>
Vector<T> &Vector<T>::operator/=(const Vector<U> &other)
{
    *this = static_cast<Vector<T>>(*this / other);
    return *this;
}

// Перегрузка оператора /
template <ContainerType T>
template <ConvertAssignableDiv<T> U>
decltype(auto) Vector<T>::operator/(const U &num) const
{
    this->check_vector_size(this->container_size, __LINE__);
    using ResultType = decltype((*this)[0] / num);
    Vector<ResultType> result(*this);

    std::ranges::transform(*this, result.begin(),
                           [&num](const U &value)
                           { return value - num; });

    return result;
}

// Перегрузка оператора /=
template <ContainerType T>
template <ConvertAssignableDiv<T> U>
Vector<T> &Vector<T>::operator/=(const U &num)
{
    *this = static_cast<Vector<T>>(*this / num);
    return *this;
}

// Векторное умножение
template <ContainerType T>
template <ValidContainer<T> Con>
decltype(auto) Vector<T>::operator^(const Con &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    if (this->container_size != 3)
    {
        time_t now = time(NULL);
        throw errSizeNotCompatible(__FILE__, __LINE__, typeid(*this).name(), ctime(&now));
    }

    using new_type = decltype((*this)[0] * other[0]);
    Vector<new_type> result;

    new_type cx = (*this)[1] * other[2] - (*this)[2] * other[1];
    new_type cy = (*this)[2] * other[0] - (*this)[0] * other[2];
    new_type cz = (*this)[0] * other[1] - (*this)[1] * other[0];

    result = {cx, cy, cz};
    return result;
}

template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::operator^=(const Con &other)
{
    *this = *this ^ other;
    return *this;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T> &Vector<T>::operator^=(std::initializer_list<U> arr)
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(arr.size(), __LINE__);
    this->check_size_equal(arr.size(), __LINE__);

    if (this->container_size != 3)
    {
        time_t now = time(NULL);
        throw errSizeNotCompatible(__FILE__, __LINE__, typeid(*this).name(), ctime(&now));
    }

    T cx = (*this)[1] * arr[2] - (*this)[2] * arr[1];
    T cy = (*this)[2] * arr[0] - (*this)[0] * arr[2];
    T cz = (*this)[0] * arr[1] - (*this)[1] * arr[0];

    *this = {cx, cy, cz};
    return *this;
}

template <ContainerType T>
template <ConvertAssignableOperationable<T> U>
decltype(auto) Vector<T>::operator^(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    if (this->container_size != 3)
    {
        time_t now = time(NULL);
        throw errSizeNotCompatible(__FILE__, __LINE__, typeid(*this).name(), ctime(&now));
    }

    using new_type = decltype((*this)[0] * other[0]);
    Vector<new_type> result;

    new_type cx = (*this)[1] * other[2] - (*this)[2] * other[1];
    new_type cy = (*this)[2] * other[0] - (*this)[0] * other[2];
    new_type cz = (*this)[0] * other[1] - (*this)[1] * other[0];

    result = {cx, cy, cz};
    return result;
}

template <ContainerType T>
template <ConvertAssignableOperationable<T> U>
Vector<T> &Vector<T>::operator^=(const Vector<U> &other)
{
    *this = *this ^ other;
    return *this;
}

// Скалярное произведение векторов
template <ContainerType T>
template <ValidContainer<T> Con>
double Vector<T>::operator&(const Con &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    return std::inner_product(
        this->cbegin(), this->cend(),
        other.cbegin(),
        static_cast<double>(0));
}

template <ContainerType T>
template <ConvertAssignableOperationable<T> U>
double Vector<T>::operator&(const Vector<U> &other) const
{
    this->check_vector_size(this->container_size, __LINE__);
    this->check_vector_size(other.size(), __LINE__);
    this->check_size_equal(other.size(), __LINE__);

    return std::inner_product(
        this->cbegin(), this->cend(),
        other.cbegin(),
        static_cast<double>(0));
}

// перегрузка оператора равно
template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T> &Vector<T>::operator=(const std::initializer_list<U> &arr)
{
    this->container_size = arr.size();
    this->memory_allocation(this->container_size, __LINE__);

    std::copy(arr.begin(), arr.end(), this->begin());
    return *this;
}

// перегрузка оператора равно
template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::operator=(const Con &other)
{
    this->check_vector_size(other.size(), __LINE__);
    this->container_size = other.size();
    this->memory_allocation(this->container_size, __LINE__);

    std::copy(other.begin(), other.end(), this->begin());
    return *this;
}

template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::operator=(Con &&other) noexcept
{
    this->check_vector_size(other.size(), __LINE__);

    this->container_size = other.size();
    this->memory_allocation(this->container_size, __LINE__);

    this->container = other.container;
    return *this;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T> &Vector<T>::operator=(const Vector<U> &other)
{
    this->check_vector_size(other.size(), __LINE__);
    this->container_size = other.size();
    this->memory_allocation(this->container_size, __LINE__);

    std::copy(other.begin(), other.end(), this->begin());
    return *this;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
Vector<T> &Vector<T>::operator=(Vector<U> &&other) noexcept
{
    this->container_size = other.size();
    this->memory_allocation(this->container_size, __LINE__);

    this->container = other.container;
    return *this;
}

// Перегрузка оператора ==
template <ContainerType T>
template <ValidContainer<T> Con>
bool Vector<T>::operator==(const Con &other) const
{
    if (this->container_size == std::ranges::size(other))
    {
        return std::ranges::equal(*this, other,
                                  [](const T &a, const auto &b)
                                  {
                                      return std::fabs(a - b) <= EPS;
                                  });
    }
    return false;
}

// Перегрузка оператора ==
template <ContainerType T>
template <ConvertAssignable<T> U>
bool Vector<T>::operator==(std::initializer_list<U> arr) const
{
    if (this->container_size == std::ranges::size(arr))
    {
        return std::ranges::equal(*this, arr,
                                  [](const T &a, const auto &b)
                                  {
                                      return std::fabs(a - b) <= EPS;
                                  });
    }
    return false;
}

// Перегрузка оператора !=
template <ContainerType T>
template <ValidContainer<T> Con>
bool Vector<T>::operator!=(const Con &other) const
{
    return !(*this == other);
}

template <ContainerType T>
template <ConvertAssignable<T> U>
bool Vector<T>::operator==(const Vector<T> &other) const
{
    if (this->container_size == std::ranges::size(other))
    {
        return std::ranges::equal(*this, other,
                                  [](const T &a, const auto &b)
                                  {
                                      return std::fabs(a - b) <= EPS;
                                  });
    }
    return false;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
bool Vector<T>::operator!=(const Vector<T> &other) const
{
    return !(*this == other);
}

// Перегрузка оператора []
template <ContainerType T>
typename Vector<T>::reference Vector<T>::operator[](int index)
{
    return get_item(index);
}

// Перегрузка оператора []
template <ContainerType T>
typename Vector<T>::const_reference Vector<T>::operator[](int index) const
{
    return get_item(index);
}

// Оператор отрицание
template <ContainerType T>
Vector<T> Vector<T>::operator-(void)
{
    this->check_vector_size(this->container_size, __LINE__);
    Vector<T> result(*this);

    result *= -1;
    return result;
}

// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// | Методы для вектора. Эквивалентные перегруженным операторам |
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

// Векторная сумма
template <ContainerType T>
template <ValidContainer<T> Con>
decltype(auto) Vector<T>::vec_sum(const Con &other) const
{
    return *this + other;
}

// Векторная сумма
template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::vec_sum_eq(const Con &other)
{
    *this = static_cast<Vector<T>>(*this + other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignableSum<T> U>
decltype(auto) Vector<T>::vec_sum(const Vector<U> &other) const
{
    return *this + other;
}

template <ContainerType T>
template <ConvertAssignableSum<T> U>
Vector<T> &Vector<T>::vec_sum_eq(const Vector<U> &other)
{
    *this = static_cast<Vector<T>>(*this + other);
    return *this;
}

// Сложение вектора с числом
template <ContainerType T>
template <ConvertAssignableSum<T> U>
decltype(auto) Vector<T>::plus(const U &num)
{
    return *this + num;
}

// Сложение вектора с числом
template <ContainerType T>
template <ConvertAssignableSum<T> U>
Vector<T> &Vector<T>::plus_eq(const U &num)
{
    *this = static_cast<Vector<T>>(*this + num);
    return *this;
}

// Вычитание вектора из вектора
template <ContainerType T>
template <ValidContainer<T> Con>
decltype(auto) Vector<T>::vec_sub(const Con &other) const
{
    return *this - other;
}

// Вычитание вектора из вектора
template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::vec_sub_eq(const Con &other)
{
    *this = static_cast<Vector<T>>(*this - other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignableSub<T> U>
decltype(auto) Vector<T>::vec_sub(const Vector<U> &other) const
{
    return *this - other;
}

template <ContainerType T>
template <ConvertAssignableSub<T> U>
Vector<T> &Vector<T>::vec_sub_eq(const Vector<U> &other)
{
    *this = static_cast<Vector<T>>(*this - other);
    return *this;
}

// Вычитание числа из вектора
template <ContainerType T>
template <ConvertAssignableSub<T> U>
decltype(auto) Vector<T>::minus(const U &num) const
{
    return *this - num;
}

// Вычитание числа из вектора
template <ContainerType T>
template <ConvertAssignableSub<T> U>
Vector<T> &Vector<T>::minus_eq(const U &num)
{
    *this = static_cast<Vector<T>>(*this - num);
    return *this;
}

// Поэлементное умножение
template <ContainerType T>
template <ValidContainer<T> Con>
decltype(auto) Vector<T>::vec_el_mul(const Con &other) const
{
    return *this * other;
}

// // Поэлементное умножение
template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::vec_el_mul_eq(const Con &other)
{
    *this = static_cast<Vector<T>>(*this * other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignableMul<T> U>
decltype(auto) Vector<T>::vec_el_mul(const Vector<U> &other) const
{
    return *this * other;
}

template <ContainerType T>
template <ConvertAssignableMul<T> U>
Vector<T> &Vector<T>::vec_el_mul_eq(const Vector<U> &other)
{
    *this = static_cast<Vector<T>>(*this * other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignableMul<T> U>
decltype(auto) Vector<T>::mul(const U &num) const
{
    return *this * num;
}

// Поэлементное умножение
template <ContainerType T>
template <ConvertAssignableMul<T> U>
Vector<T> &Vector<T>::mul_eq(const U &num)
{
    *this = static_cast<Vector<T>>(*this * num);
    return *this;
}

// Поэлементное Деление
template <ContainerType T>
template <ValidContainer<T> Con>
decltype(auto) Vector<T>::vec_el_div(const Con &other) const
{
    return *this / other;
}

// Поэлементное Деление
template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::vec_el_div_eq(const Con &other)
{
    *this = static_cast<Vector<T>>(*this / other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignableDiv<T> U>
decltype(auto) Vector<T>::vec_el_div(const Vector<U> &other) const
{
    return *this / other;
}

template <ContainerType T>
template <ConvertAssignableDiv<T> U>
Vector<T> &Vector<T>::vec_el_div_eq(const Vector<U> &other)
{
    *this = static_cast<Vector<T>>(*this / other);
    return *this;
}

// Деление вектора на число
template <ContainerType T>
template <ConvertAssignableDiv<T> U>
decltype(auto) Vector<T>::div(const U &num) const
{
    return *this / num;
}

// Деление вектора на число
template <ContainerType T>
template <ConvertAssignableDiv<T> U>
Vector<T> &Vector<T>::div_eq(const U &num)
{
    *this = static_cast<Vector<T>>(*this / num);
    return *this;
}

// Векторное умножение
template <ContainerType T>
template <ValidContainer<T> Con>
decltype(auto) Vector<T>::vec_mul(const Con &other) const
{
    return *this ^ other;
}

// Векторное умножение
template <ContainerType T>
template <ValidContainer<T> Con>
Vector<T> &Vector<T>::vec_mul_eq(const Con &other)
{
    *this = static_cast<Vector<T>>(*this ^ other);
    return *this;
}

template <ContainerType T>
template <ConvertAssignableOperationable<T> U>
decltype(auto) Vector<T>::vec_mul(const Vector<U> &other) const
{
    return *this ^ other;
}

template <ContainerType T>
template <ConvertAssignableOperationable<T> U>
Vector<T> &Vector<T>::vec_mul_eq(const Vector<U> &other)
{
    *this = static_cast<Vector<T>>(*this ^ other);
    return *this;
}

// Скалярное умножение
template <ContainerType T>
template <ValidContainer<T> Con>
double Vector<T>::scal_mul(const Con &other)
{
    return *this & other;
}

template <ContainerType T>
template <ConvertAssignableOperationable<T> U>
double Vector<T>::scal_mul(const Vector<U> &other)
{
    return *this & other;
}

// Метод
template <ContainerType T>
template <ValidContainer<T> Con>
bool Vector<T>::is_equal(const Con &other) const
{
    return *this == other;
}

template <ContainerType T>
template <ConvertAssignable<T> U>
bool Vector<T>::is_equal(const Vector<U> &other) const
{
    return *this == other;
}

template <ContainerType T>
void Vector<T>::print(void) const
{
    std::ranges::copy(*this,
                      std::ostream_iterator<typename T::value_type>(std::cout, " "));
    std::cout << '\n';
}

template <ContainerType T>
Vector<T> Vector<T>::negative(void)
{
    return -(*this);
}

// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// |                          Приватные функции                                |
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––

template <ContainerType T>
void Vector<T>::memory_allocation(const int &container_size, int line)
{
    try
    {
        container.reset(new T[this->container_size], std::default_delete<T[]>());
    }
    catch (std::bad_alloc &exc)
    {
        time_t now = time(NULL);
        throw errMemory(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}

// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
// | Приватные функции, проверяющие входные параметры. Выбрасывают исключения  |
// –––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––
template <ContainerType T>
void Vector<T>::check_vector_size(baseContainer::size_type size, int line) const
{
    if (size <= 0)
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

template <ContainerType T>
void Vector<T>::check_index(int index, int line) const
{
    if (index < 0 || index >= this->container_size)
    {
        time_t now = time(NULL);
        throw errIndexOutOfRange(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}

/// @brief Функция проверяет эквивалентность размера текущего объекта и введенного значения
/// @tparam T type
/// @param size Размер второго вектора/ значение, с которым нужно сравнить
/// @param line Номер строки, нужен для сообщение об ошибке
template <ContainerType T>
void Vector<T>::check_size_equal(baseContainer::size_type size, int line) const
{
    this->check_vector_size(this->container_size, __LINE__);
    if (std::fabs(this->container_size - size) > EPS)
    {
        time_t now = time(NULL);
        throw errVectorsSizeNotEqual(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}

template <ContainerType T>
void Vector<T>::fill_elements_va(VectorIterator<T> iter, size_t remaining, va_list &args)
{
    if (remaining == 0)
        return;

    using ArgType = decltype(va_arg(args, T));
    *iter = va_arg(args, ArgType);
    fill_elements_va(++iter, remaining - 1, args);
}
