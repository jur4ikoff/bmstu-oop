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
#pragma region aliases
    using value_type = T;
    using iterator = VectorIterator<T>;
    using const_iterator = VectorConstIterator<T>;

    friend class VectorIterator<T>;
    friend class VectorConstIterator<T>;
#pragma endregion aliases

#pragma region Constructors
    // Обычный конструктор
    Vector();
    explicit Vector(const Vector<T> &other); // Конструктор копирования
    Vector(Vector<T> &&other) noexcept;      // Копирование по правой ссылке на вектор этого же типа

    template <ConvertAssignable<T> T1>
    Vector(const Vector<T1> &other); // Преобразование из другого моего вектора

    template <ValidContainer<T> Con>
    Vector(const Con &other); // Преобразование из контейнера

    explicit Vector(const int &size); // конструктор по рамзеру

    template <ConvertAssignable<T> T1>
    Vector(std::initializer_list<T1> arr); // Конструктор по списку инициализации Vector vec = {1, 2, 3, 4};

#pragma endregion Constructors

    // Преобразование из другого контейнера
    // template <ConvertAssignable<T> T1>
    // Vector(const Vector<T1> &other);

    // Возвращает иттератор на начало вектора
    VectorIterator<T> begin(void) noexcept;
    VectorIterator<T> end(void) noexcept;

    // Возвращает константный интератор на начало/кенец вектора
    VectorConstIterator<T> cbegin(void) const noexcept;
    VectorConstIterator<T> cend(void) const noexcept;

    ~Vector() = default;

protected:
    void memory_allocation(const int &size, int line);

    void check_vector_size(const int &size, int line);

private:
    std::shared_ptr<T[]> container;
};

#include "vector.hpp"
