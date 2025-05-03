#pragma once

#include <memory>

#include "base_iterator.h"

template <ContainerType T>
class Vector;

template <ContainerType T>
class VectorIterator : public BaseIterator<T>
{
public:
    VectorIterator() = default;                    // Пустой конструктор
    VectorIterator(const VectorIterator<T> &iter); // Конструктор по иттератору
    VectorIterator(const Vector<T> &vec);          // Коструктор по контейнеру
    ~VectorIterator() = default;                   // Деструктор

    // Перегрузка оператора =
    VectorIterator<T> &operator=(const VectorIterator<T> &other);

    // Перегруза операторов * и ->
    T &operator*();
    T *operator->();

    // Перегрузка оператроа +
    VectorIterator<T> operator+(const int i) const;
    VectorIterator<T> &operator+=(const int i);

    // Перегрузка инкремента
    VectorIterator<T> &operator++();   // ++iter
    VectorIterator<T> operator++(int); // iter++

    // VectorIterator<T> &operator -- ();
    // VectorIterator<T> operator -- (int);
};

#include "vector_iterator.hpp"