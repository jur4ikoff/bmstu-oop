#pragma once

#include <memory>

#include "base_reverse_iterator.h"
#include "vector_reverse_iterator.h"

template <ContainerType T>
class Vector;

template <ContainerType T>
class VectorConstReverseIterator;

template <ContainerType T>
VectorConstReverseIterator<T> operator+(typename BaseReverseIterator<T>::difference_type n, const VectorConstReverseIterator<T> &other);

template <ContainerType T>
class VectorConstReverseIterator final : public BaseReverseIterator<T>
{
public:
    VectorConstReverseIterator() = default;                    // Пустой конструктор
    VectorConstReverseIterator(const VectorConstReverseIterator<T> &iter); // Конструктор по иттератору
    VectorConstReverseIterator(const VectorReverseIterator<T> &iter);
    VectorConstReverseIterator(const Vector<T> &vec);          // Коструктор по контейнеру
    ~VectorConstReverseIterator() = default;                   // Деструктор

    // Перегруза операторов * и ->
    T &operator*() const;
    T *operator->() const;

    // Перегрузка оператора =
    VectorConstReverseIterator<T> &operator=(const VectorConstReverseIterator<T> &other);

    // Перегрузка оператроа +
    VectorConstReverseIterator<T> operator+(const int i) const;
    VectorConstReverseIterator<T> &operator+=(const int i);
    friend VectorConstReverseIterator<T>(::operator+ <>)(typename BaseReverseIterator<T>::difference_type n, const VectorConstReverseIterator<T> &other);

    // Перегрузка инкремента
    VectorConstReverseIterator<T> &operator++();  
    VectorConstReverseIterator<T> operator++(int);

    // Перегрузка оператора -
    VectorConstReverseIterator<T> operator-(const int i) const;
    VectorConstReverseIterator<T> &operator-=(const int i);

    // Перегрузка декремента
    VectorConstReverseIterator<T> &operator--(); 
    VectorConstReverseIterator<T> operator--(int); 

    T &operator[](int index) const;

    explicit operator bool() const;

    typename BaseReverseIterator<T>::difference_type operator-(const VectorConstReverseIterator<T> &other) const;
};

static_assert(std::random_access_iterator<VectorConstReverseIterator<int>>);

#include "vector_const_reverse_iterator.hpp"
