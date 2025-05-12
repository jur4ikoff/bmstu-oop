#pragma once

#include <memory>

#include "base_reverse_iterator.h"

template <ContainerType T>
class Vector;

template <ContainerType T>
class VectorReverseIterator;

template <ContainerType T>
VectorReverseIterator<T> operator+(typename BaseReverseIterator<T>::difference_type n, const VectorReverseIterator<T> &other);

template <ContainerType T>
class VectorReverseIterator final : public BaseReverseIterator<T>
{
public:
    VectorReverseIterator() = default;                    // Пустой конструктор
    VectorReverseIterator(const VectorReverseIterator<T> &iter); // Конструктор по иттератору
    VectorReverseIterator(const Vector<T> &vec);          // Коструктор по контейнеру
    ~VectorReverseIterator() = default;                   // Деструктор

    // Перегруза операторов * и ->
    T &operator*() const;
    T *operator->() const;

    // Перегрузка оператора =
    VectorReverseIterator<T> &operator=(const VectorReverseIterator<T> &other);

    // Перегрузка оператроа +
    VectorReverseIterator<T> operator+(const int i) const;
    VectorReverseIterator<T> &operator+=(const int i);
    friend VectorReverseIterator<T>(::operator+ <>)(typename BaseReverseIterator<T>::difference_type n, const VectorReverseIterator<T> &other);

    // Перегрузка инкремента
    VectorReverseIterator<T> &operator++();   // ++iter
    VectorReverseIterator<T> operator++(int); // iter++

    // Перегрузка оператора -
    VectorReverseIterator<T> operator-(const int i) const;
    VectorReverseIterator<T> &operator-=(const int i);

    // Перегрузка декремента
    VectorReverseIterator<T> &operator--();   // --iter
    VectorReverseIterator<T> operator--(int); // iter--

    T &operator[](int index) const;

    explicit operator bool() const;

    typename BaseReverseIterator<T>::difference_type operator-(const VectorReverseIterator<T> &other) const;
};

static_assert(std::random_access_iterator<VectorReverseIterator<int>>);

#include "vector_reverse_iterator.hpp"
