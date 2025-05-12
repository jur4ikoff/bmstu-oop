#pragma once

#include <memory>

#include "base_reverse_iterator.h"
#include "vector_const_reverse_iterator.h"

template <ContainerType T>
class Vector;

template <ContainerType T>
class VectorReverseIterator;

template <ContainerType T>
class VectorConstReverseIterator;

template <ContainerType T>
VectorReverseIterator<T> operator+(typename BaseReverseIterator<T>::difference_type n, const VectorReverseIterator<T> &other) noexcept;

template <ContainerType T>
class VectorReverseIterator final : public BaseReverseIterator<T>
{
public:
    friend class VectorConstReverseIterator<T>;
    VectorReverseIterator() = default;                                    // Пустой конструктор
    VectorReverseIterator(const VectorReverseIterator<T> &iter) noexcept; // Конструктор по иттератору
    VectorReverseIterator(const Vector<T> &vec) noexcept;                 // Коструктор по контейнеру
    ~VectorReverseIterator() = default;                                   // Деструктор

    // Перегруза операторов * и ->
    BaseReverseIterator<T>::reference operator*() const;
    BaseReverseIterator<T>::pointer operator->() const;
    BaseReverseIterator<T>::reference operator[](int index) const;

    // Перегрузка оператора =
    VectorReverseIterator<T> &operator=(const VectorReverseIterator<T> &other);

    // Перегрузка оператроа +
    VectorReverseIterator<T> operator+(const int i) const noexcept;
    VectorReverseIterator<T> &operator+=(const int i) noexcept;
    friend VectorReverseIterator<T>(::operator+ <>)(typename BaseReverseIterator<T>::difference_type n, const VectorReverseIterator<T> &other) noexcept;
    VectorReverseIterator<T> &operator++() noexcept; // Перегрузка инкремента
    VectorReverseIterator<T> operator++(int) noexcept;

    // Перегрузка оператора -
    VectorReverseIterator<T> operator-(const int i) const noexcept;
    VectorReverseIterator<T> &operator-=(const int i) noexcept;
    VectorReverseIterator<T> &operator--() noexcept; // Перегрузка декремента
    VectorReverseIterator<T> operator--(int) noexcept;
    typename BaseReverseIterator<T>::difference_type operator-(const VectorReverseIterator<T> &other) const noexcept;
};

static_assert(std::random_access_iterator<VectorReverseIterator<int>>);

#include "vector_reverse_iterator.hpp"
