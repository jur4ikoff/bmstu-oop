#pragma once

#include <memory>

#include "base_reverse_iterator.h"
#include "vector_reverse_iterator.h"

template <ContainerType T>
class Vector;

template <ContainerType T>
class VectorConstReverseIterator;

template <ContainerType T>
VectorConstReverseIterator<T> operator+(typename BaseReverseIterator<T>::difference_type n, const VectorConstReverseIterator<T> &other) noexcept;

template <ContainerType T>
class VectorConstReverseIterator final : public BaseReverseIterator<T>
{
public:
    VectorConstReverseIterator() = default;                                         // Пустой конструктор
    VectorConstReverseIterator(const VectorConstReverseIterator<T> &iter) noexcept; // Конструктор по иттератору
    VectorConstReverseIterator(const VectorReverseIterator<T> &iter) noexcept;
    VectorConstReverseIterator(const Vector<T> &vec) noexcept; // Коструктор по контейнеру
    ~VectorConstReverseIterator() = default;                   // Деструктор

    // Перегрузка оператора =
    VectorConstReverseIterator<T> &operator=(const VectorConstReverseIterator<T> &other);

    // Перегрузка оператроа +
    VectorConstReverseIterator<T> operator+(const int i) const noexcept;
    VectorConstReverseIterator<T> &operator+=(const int i) noexcept;
    friend VectorConstReverseIterator<T>(::operator+ <>)(typename BaseReverseIterator<T>::difference_type n, const VectorConstReverseIterator<T> &other) noexcept;

    // Перегрузка инкремента
    VectorConstReverseIterator<T> &operator++() noexcept;
    VectorConstReverseIterator<T> operator++(int) noexcept;

    // Перегрузка оператора -
    VectorConstReverseIterator<T> operator-(const int i) const noexcept;
    VectorConstReverseIterator<T> &operator-=(const int i) noexcept;

    // Перегрузка декремента
    VectorConstReverseIterator<T> &operator--() noexcept;
    VectorConstReverseIterator<T> operator--(int) noexcept;

    const T &operator[](int index) const;

    explicit operator bool() const noexcept;

    typename BaseReverseIterator<T>::difference_type operator-(const VectorConstReverseIterator<T> &other) const noexcept;
};

static_assert(std::random_access_iterator<VectorConstReverseIterator<int>>);

#include "vector_const_reverse_iterator.hpp"
