#pragma once

#include "base_container.h"
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

    using size_type = int;

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

    explicit Vector(const int &container_size); // конструктор по рамзеру

    template <ConvertAssignable<T> U>
    Vector(std::initializer_list<U> arr); // Конструктор по списку иницалиизации

    template <ConvertAssignable<T> U>
    Vector(int container_size, const U *arr); // Конструктор по размеру и массиву заполнения

    template <ConvertAssignable<T> U>
    Vector(int container_size, U elem, ...); // По длине и параметрам, для заполнения

    template <ForwardIterator U>
    Vector(U begin, U end);

#pragma endregion Constructors

    // Функция возвращает математическую длину вектора
    decltype(auto) len();

    /**
     * @brief Функция нормализует вектор
     * @return Новый, нормализованный вектор
     */
    decltype(auto) normalization(void) const;

    // Возвращает иттератор на начало вектора
    VectorIterator<T> begin(void) noexcept;
    VectorIterator<T> end(void) noexcept;

    // Возвращает константный интератор на начало/кенец вектора
    VectorConstIterator<T> cbegin(void) const noexcept;
    VectorConstIterator<T> cend(void) const noexcept;

    ~Vector() = default;

protected:
    void memory_allocation(const int &container_size, int line);

    void check_vector_size(const int &container_size, int line) const;
    void check_arr_null(const T *arr, int line) const;

    template <typename U>
    void check_division_zero(const U &num, int line) const;

private:
    std::shared_ptr<T[]> container;
};

#include "vector.hpp"
