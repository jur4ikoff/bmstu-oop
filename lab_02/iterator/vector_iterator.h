#pragma once

#include <memory>

#include "base_iterator.h"
#include "vector_const_iterator.h"

template <ContainerType T>
class Vector;

template <ContainerType T>
class VectorIterator;

template <ContainerType T>
VectorIterator<T> operator+(typename BaseIterator<T>::difference_type n, const VectorIterator<T> &other) noexcept;

template <ContainerType T>
class VectorIterator final : public BaseIterator<T>
{
    friend class VectorConstIterator<T>;
public:
    VectorIterator() = default;                             // Пустой конструктор
    VectorIterator(const VectorIterator<T> &iter) noexcept; // Конструктор по иттератору
    VectorIterator(const Vector<T> &vec) noexcept;          // Коструктор по контейнеру
    ~VectorIterator() = default;                            // Деструктор

    // Перегруза операторов * и ->
    T &operator*() const;
    T *operator->() const;

    // Перегрузка оператора =
    VectorIterator<T> &operator=(const VectorIterator<T> &other);

    // Перегрузка оператроа +
    VectorIterator<T> operator+(int n) const noexcept;
    VectorIterator<T> &operator+=(const int n) noexcept;
    friend VectorIterator<T>(::operator+ <>)(typename BaseIterator<T>::difference_type n, const VectorIterator<T> &other) noexcept;

    // Перегрузка инкремента
    VectorIterator<T> &operator++() noexcept;
    VectorIterator<T> operator++(int) noexcept;

    // Перегрузка оператора -
    VectorIterator<T> operator-(const int n) const noexcept;
    VectorIterator<T> &operator-=(const int n) noexcept;

    // Перегрузка декремента
    VectorIterator<T> &operator--() noexcept;
    VectorIterator<T> operator--(int) noexcept;

    T &operator[](int index) const;

    explicit operator bool() const noexcept;

    typename BaseIterator<T>::difference_type operator-(const VectorIterator<T> &other) const noexcept;
};

static_assert(std::random_access_iterator<VectorIterator<int>>);

#include "vector_iterator.hpp"
