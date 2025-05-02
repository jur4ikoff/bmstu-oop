#pragma once

#include "base_container.hpp"
#include "vector_concepts.hpp"
#include "vector_const_iterator.h"
#include "vector_iterator.h"

#include <iostream>
#include <memory>

template <ContainerType T>
class Vector : public baseContainer
{
public:
    using value_type = T;
    using iterator = VectorIterator<T>;
    using const_iterator = VectorConstIterator<T>;

    friend class VectorIterator<T>;
    friend class VectorConstIterator<T>;

    // Обычный конструктор
    Vector();

    // Конструктор копирования
    explicit Vector(const Vector<T> &other);
    // Преобразование из другого контейнера
    // template <ConvertAssignable<T> T1>
    // Vector(const Vector<T1> &other);

    // Возвращает иттератор на начало вектора
    VectorIterator<T> begin(void) noexcept;
    // Итератор на конец вектора
    VectorIterator<T> end(void) noexcept;

    // Возвращает константный интератор на начало/кенец вектора
    VectorConstIterator<T> cbegin(void) const noexcept;
    VectorConstIterator<T> cend(void) const noexcept;

    ~Vector() = default;

protected:
    void memory_allocation(const size_t &size, int line);

private:
    std::shared_ptr<T[]> container;
};

#include "vector.hpp"
