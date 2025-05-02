#pragma once

#include <memory>

#include "base_iterator.h"

template <ContainerType T>
class Vector;

template <ContainerType T>
class VectorIterator : public ContainerBaseIterator<T>
{
public:
    // Пустой конструктор
    VectorIterator() = default;

    // Конструктор по иттератору
    VectorIterator(const VectorIterator<T> &iter);

    // Коструктор по контейнеру
    VectorIterator(const VectorIterator<T> &vec);

    // Деструктор
    ~VectorIterator() = default;
    
}
