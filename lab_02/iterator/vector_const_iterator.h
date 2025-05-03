#pragma once

#include <memory>

#include "base_iterator.h"
#include "vector_iterator.h"

template <ContainerType T>
class Vector;

template <ContainerType T>
class VectorConstIterator : public BaseIterator<T>
{
public:
    VectorConstIterator() = default;                         // Пустой конструктор
    VectorConstIterator(const VectorConstIterator<T> &iter); // Конструктор по итератору
    VectorConstIterator(const VectorIterator<T> &iter);      // Конструктор от обычного итератора
    VectorConstIterator(const Vector<T> &vec);               // Коструктор по контейнеру
    ~VectorConstIterator() = default;                        // Деструктор
    
    VectorConstIterator<T> &operator=(const VectorConstIterator<T> &other); // Перегрузка оператора =
    VectorConstIterator<T> operator+(const int i) const; // Перегрузка оператора +
    VectorConstIterator<T> &operator+=(const int i); // Перегрузка оператора +=

    // Перегрузка инкремента
    VectorConstIterator<T> &operator++();   // ++iter
    VectorConstIterator<T> operator++(int); // iter++

    // VectorConstIterator<T> &operator -- ();
    // VectorConstIterator<T> operator -- (int);
};

#include "vector_const_iterator.hpp"
