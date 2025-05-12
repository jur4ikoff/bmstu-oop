#pragma once

#include <memory>

#include "base_reverse_iterator.h"

template <ContainerType T>
class Vector;

template <ContainerType T>
class VectorReverseIterator;

template <ContainerType T>
VectorReverseIterator<T> operator+(typename BaseReverseIterator<T>::difference_type n, const VectorReverseIterator<T> &other) noexcept;

template <ContainerType T>
class VectorReverseIterator final : public BaseReverseIterator<T>
{
public:
    VectorReverseIterator() = default;                    // Пустой конструктор
    VectorReverseIterator(const VectorReverseIterator<T> &iter) noexcept; // Конструктор по иттератору
    VectorReverseIterator(const Vector<T> &vec) noexcept;          // Коструктор по контейнеру
    ~VectorReverseIterator() = default;                   // Деструктор

    // Перегруза операторов * и ->
    T &operator*() const;
    T *operator->() const;

    // Перегрузка оператора =
    VectorReverseIterator<T> &operator=(const VectorReverseIterator<T> &other);

    // Перегрузка оператроа +
    VectorReverseIterator<T> operator+(const int i) const noexcept;
    VectorReverseIterator<T> &operator+=(const int i) noexcept;
    friend VectorReverseIterator<T>(::operator+ <>)(typename BaseReverseIterator<T>::difference_type n, const VectorReverseIterator<T> &other) noexcept;

    // Перегрузка инкремента
    VectorReverseIterator<T> &operator++() noexcept;   // ++iter
    VectorReverseIterator<T> operator++(int) noexcept; // iter++

    // Перегрузка оператора -
    VectorReverseIterator<T> operator-(const int i) const noexcept;
    VectorReverseIterator<T> &operator-=(const int i) noexcept;

    // Перегрузка декремента
    VectorReverseIterator<T> &operator--() noexcept;   // --iter
    VectorReverseIterator<T> operator--(int) noexcept; // iter--

    T &operator[](int index) const;

    explicit operator bool() const noexcept;

    typename BaseReverseIterator<T>::difference_type operator-(const VectorReverseIterator<T> &other) const noexcept;
};

static_assert(std::random_access_iterator<VectorReverseIterator<int>>);

#include "vector_reverse_iterator.hpp"
