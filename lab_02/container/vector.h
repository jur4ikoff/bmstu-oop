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

    template <typename U>
        requires ConvertAssignable<T, U>
    Vector(const Vector<U> &other); // Преобразование из другого моего вектора

    template <typename Con>
        requires ValidContainer<T, Con>
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
    decltype(auto) len() const;

#pragma region vector_math_methods
    /**
     * @brief Функция нормализует вектор
     * @return Новый, нормализованный вектор
     */
    decltype(auto) normalization(void) const;
    bool is_normalize() const; // Функция проверяет нормализован ли вектор
    bool is_zero() const;      // Функция проверяет нулевой ли вектор

    // Функция считает угол между двумя векторами
    template <ConvertAssignable<T> U>
    decltype(auto) calc_angle(const Vector<U> &other) const;

    template <ConvertAssignable<T> U>
    bool is_colliniar(const Vector<U> &other) const;

    template <ConvertAssignable<T> U>
    bool is_orthogonal(const Vector<U> &other) const;

#pragma endregion vector_math_methods

    template <ConvertAssignable<T> U>
    void set_item(size_type index, const U &elem);

    // Получить элемент по индексу
    T &get_item(int ind);
    const T &get_item(int ind) const;

    // Возвращает иттератор на начало вектора
    VectorIterator<T> begin(void) const noexcept;
    VectorIterator<T> end(void) const noexcept;

    // Возвращает константный интератор на начало/кенец вектора
    VectorConstIterator<T> cbegin(void) const noexcept;
    VectorConstIterator<T> cend(void) const noexcept;

    // Перегрузка оператора []
    T &operator[](int ind);
    const T &operator[](int ind) const;

#pragma region div
    // Перегрузка оператора /
    template <ConvertAssignableDiv<T> T1>
    decltype(auto) operator/(const T1 &num) const;

    // Перегрузка оператора /=
    template <ConvertAssignableDiv<T> T1>
    Vector<T> &operator/=(const T1 &num);
#pragma end_region div

#pragma region equal
    // перегрузка равенства и неравенства
    template <typename Con>
        requires ValidContainer<T, Con>
    bool operator==(const Con &other) const;

    template <typename Con>
        requires ValidContainer<T, Con>
    bool operator!=(const Con &other) const;

    template <typename Con>
        requires ValidContainer<T, Con>
    bool is_equal(const Con &other) const;

    // перегрузка оператора равно

    template <Convertiable<T> U>
    Vector<T> &operator=(const std::initializer_list<U> &arr);

    template <Convertiable<T> U>
    Vector<T> &operator=(const Vector<U> &other);

#pragma endregion vector_operators

#pragma region start
    template <Convertiable<T> U>
    decltype(auto) operator&(const Vector<U> &other) const;

#pragma endregion vector_operators

    ~Vector() = default;

protected:
    void memory_allocation(const int &container_size, int line);

    void check_vector_size(const int &container_size, int line) const;
    void check_arr_null(const T *arr, int line) const;
    void check_index(const int &index, int line) const;

    template <typename U>
    void check_division_zero(const U &num, int line) const;
    void check_size_equal(const size_type &size, int line) const;

private:
    std::shared_ptr<T[]> container;
};

#include "vector.hpp"
