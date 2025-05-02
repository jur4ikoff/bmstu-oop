#pragma once

#include "base_container.hpp"
#include "vector_concepts.hpp"

#include <iostream>
#include <memory>

template <ContainerType T>
class Vector : public baseContainer
{
public:
    using value_type = T;

    // Обычный конструктор
    Vector();

    // Конструктор копирования
    explicit Vector(const Vector<T> &other);
    // Преобразование из другого контейнера
    // template <ConvertAssignable<T> T1>
    // Vector(const Vector<T1> &other);

    ~Vector() = default;

protected:
    void memory_allocation(const size_t &size, int line);

private:
    std::shared_ptr<T[]> container;
};

#include "vector.hpp"
