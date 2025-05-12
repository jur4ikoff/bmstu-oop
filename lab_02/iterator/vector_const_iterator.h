#pragma once

#include <memory>

#include "base_iterator.h"
#include "vector_iterator.h"

template <ContainerType T>
class Vector;

template <ContainerType T>
class VectorConstIterator;

template <ContainerType T>
VectorConstIterator<T> operator+(typename BaseIterator<T>::difference_type n, const VectorConstIterator<T> &other) noexcept;

template <ContainerType T>
class VectorConstIterator final : public BaseIterator<T>
{
public:
    VectorConstIterator() = default;                                  // Пустой конструктор
    VectorConstIterator(const VectorConstIterator<T> &iter) noexcept; // Конструктор по итератору
    VectorConstIterator(const VectorIterator<T> &iter) noexcept;      // Конструктор от обычного итератора
    VectorConstIterator(const Vector<T> &vec) noexcept;               // Коструктор по контейнеру
    ~VectorConstIterator() = default;                                 // Деструктор

    VectorConstIterator<T> &operator=(const VectorConstIterator<T> &other); // Перегрузка оператора =

    VectorConstIterator<T> operator+(const int n) const noexcept; // Перегрузка оператора +
    VectorConstIterator<T> &operator+=(const int n) noexcept;     // Перегрузка оператора +=
    friend VectorConstIterator<T>(::operator+ <>)(typename BaseIterator<T>::difference_type n, const VectorConstIterator<T> &other) noexcept;

    // Перегрузка инкремента
    VectorConstIterator<T> &operator++() noexcept;
    VectorConstIterator<T> operator++(int) noexcept; // ++iter

    // Перегрузка оператора -
    VectorConstIterator<T> operator-(const int n) const noexcept;
    VectorConstIterator<T> &operator-=(const int n) noexcept;

    typename BaseIterator<T>::difference_type operator-(const VectorConstIterator<T> &other) const noexcept;

    // Перегрузка декремента
    VectorConstIterator<T> &operator--() noexcept;
    VectorConstIterator<T> operator--(int) noexcept;

    const T &operator[](int index) const;

    explicit operator bool() const noexcept;
};

static_assert(std::random_access_iterator<VectorConstIterator<int>>);

#include "vector_const_iterator.hpp"
