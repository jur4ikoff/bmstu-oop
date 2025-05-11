#pragma once

#include <memory>

// #include "base_reverse_iterator.h"
// #include "vector_iterator.h"

// template <ContainerType T>
// class Vector;

// template <ContainerType T>
// class VectorConstIterator;

// template <ContainerType T>
// VectorConstIterator<T> operator+(typename BaseIterator<T>::difference_type n, const VectorConstIterator<T> &other);

// template <ContainerType T>
// class VectorConstIterator final : public BaseIterator<T>
// {
// public:
//     VectorConstIterator() = default;                         // Пустой конструктор
//     VectorConstIterator(const VectorConstIterator<T> &iter); // Конструктор по итератору
//     VectorConstIterator(const VectorIterator<T> &iter);      // Конструктор от обычного итератора
//     VectorConstIterator(const Vector<T> &vec);               // Коструктор по контейнеру
//     ~VectorConstIterator() = default;                        // Деструктор

//     VectorConstIterator<T> &operator=(const VectorConstIterator<T> &other); // Перегрузка оператора =

//     VectorConstIterator<T> operator+(const int n) const; // Перегрузка оператора +
//     VectorConstIterator<T> &operator+=(const int n);     // Перегрузка оператора +=
//     friend VectorConstIterator<T>(::operator+ <>)(typename BaseIterator<T>::difference_type n, const VectorConstIterator<T> &other);

//     // Перегрузка инкремента
//     VectorConstIterator<T> &operator++();
//     VectorConstIterator<T> operator++(int); // ++iter

//     // Перегрузка оператора -
//     VectorConstIterator<T> operator-(const int n) const;
//     VectorConstIterator<T> &operator-=(const int n);

//     typename BaseIterator<T>::difference_type operator-(const VectorConstIterator<T> &other) const;

//     // Перегрузка декремента
//     VectorConstIterator<T> &operator--();
//     VectorConstIterator<T> operator--(int);

//     T &operator[](int) const;

//     explicit operator bool() const;
// };

// // static_assert(std::random_access_iterator<VectorConstIterator<int>>);

// #include "vector_const_reverse_iterator.hpp"
