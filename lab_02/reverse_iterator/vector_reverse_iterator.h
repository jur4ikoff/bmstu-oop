#pragma once

// #include <memory>

// #include "base_reverse_iterator.h"

// template <ContainerType T>
// class Vector;

// template <ContainerType T>
// class VectorIterator;

// template <ContainerType T>
// VectorIterator<T> operator+(typename BaseIterator<T>::difference_type n, const VectorIterator<T> &other);

// template <ContainerType T>
// class VectorIterator final : public BaseIterator<T>
// {
// public:
//     VectorIterator() = default;                    // Пустой конструктор
//     VectorIterator(const VectorIterator<T> &iter); // Конструктор по иттератору
//     VectorIterator(const Vector<T> &vec);          // Коструктор по контейнеру
//     ~VectorIterator() = default;                   // Деструктор

//     // Перегруза операторов * и ->
//     T &operator*() const;
//     T *operator->() const;

//     // Перегрузка оператора =
//     VectorIterator<T> &operator=(const VectorIterator<T> &other);

//     // Перегрузка оператроа +
//     VectorIterator<T> operator+(const int i) const;
//     VectorIterator<T> &operator+=(const int i);
//     friend VectorIterator<T>(::operator+ <>)(typename BaseIterator<T>::difference_type n, const VectorIterator<T> &other);

//     // Перегрузка инкремента
//     VectorIterator<T> &operator++();   // ++iter
//     VectorIterator<T> operator++(int); // iter++

//     // Перегрузка оператора -
//     VectorIterator<T> operator-(const int i) const;
//     VectorIterator<T> &operator-=(const int i);

//     // Перегрузка декремента
//     VectorIterator<T> &operator--();   // --iter
//     VectorIterator<T> operator--(int); // iter--

//     T &operator[](int) const;

//     explicit operator bool() const;

//     typename BaseIterator<T>::difference_type operator-(const VectorIterator<T> &other) const;
// };

// static_assert(std::random_access_iterator<VectorIterator<int>>);

// #include "vector_reverse_iterator.hpp"
