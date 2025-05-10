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

#pragma region vector_math_methods
    // Функция возвращает математическую длину вектора
    decltype(auto) len() const;

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

#pragma region iterators
    // Возвращает иттератор на начало вектора
    VectorIterator<T> begin(void) const noexcept;
    VectorIterator<T> end(void) const noexcept;

    // Возвращает константный интератор на начало/кенец вектора
    VectorConstIterator<T> cbegin(void) const noexcept;
    VectorConstIterator<T> cend(void) const noexcept;
#pragma endregion iterators

#pragma region operators
    // Перегрузка +
    // Перегрузка оператора + для вектора
    template <ConvertAssignableSum<T> U>
    decltype(auto) operator+(const Vector<U> &other) const;
    template <ConvertAssignableSum<T> U>
    Vector<T> &operator+=(const Vector<U> &other);

    // Сложение вектора и числа
    template <ConvertAssignableSum<T> U>
    decltype(auto) operator+(const U &num) const;
    template <ConvertAssignableSum<T> U>
    Vector<T> &operator+=(const U &num);

    // Перегрузка -
    // Перегрузка оператора - для вектора
    template <ConvertAssignableSub<T> U>
    decltype(auto) operator-(const Vector<U> &other) const;
    template <ConvertAssignableSub<T> U>
    Vector<T> &operator-=(const Vector<U> &other);

    // Перегрзука оператора - для числа
    template <ConvertAssignableSub<T> U>
    decltype(auto) operator-(const U &num) const;
    template <ConvertAssignableSub<T> U>
    Vector<T> &operator-=(const U &num);

    // Перегрузка *
    // Перегрузка оператора умножения для вектора
    template <ConvertAssignableMul<T> U>
    decltype(auto) operator*(const Vector<U> &other) const;
    template <ConvertAssignableMul<T> U>
    Vector<T> &operator*=(const Vector<U> &other);

    // Перегрзука оператора * для числа
    template <ConvertAssignableMul<T> U>
    decltype(auto) operator*(const U &num) const;
    template <ConvertAssignableMul<T> U>
    Vector<T> &operator*=(const U &num);

    // Перегрузка /
    // Перегрузка оператора /. Поэлементное деление вектора на вектор
    template <ConvertAssignableDiv<T> U>
    decltype(auto) operator/(const Vector<U> &other) const;
    template <ConvertAssignableDiv<T> U>
    Vector<T> &operator/=(const Vector<U> &other);

    // Перегрузка оператора / деление на число
    template <ConvertAssignableDiv<T> U>
    decltype(auto) operator/(const U &num) const;
    template <ConvertAssignableDiv<T> U>
    Vector<T> &operator/=(const U &num);

    // векторное умножение
    template <ConvertAssignableOperationable<T> U>
    decltype(auto) operator^(const Vector<U> &other) const;
    template <ConvertAssignableOperationable<T> U>
    Vector<T> &operator^=(const Vector<U> &other);

    // перегрузка оператора & - Скалярное умножение
    template <ConvertAssignableOperationable<T> U>
    decltype(auto) operator&(const Vector<U> &other) const;

    // перегрузка оператора равно
    template <ConvertAssignable<T> U>
    Vector<T> &operator=(const std::initializer_list<U> &arr);
    template <ConvertAssignable<T> U>
    Vector<T> &operator=(const Vector<U> &other);
    template <ConvertAssignable<T> U>
    Vector<T> &operator=(const Vector<U> &&other);

    // перегрузка равенства и неравенства
    template <typename Con>
        requires ValidContainer<T, Con>
    bool operator==(const Con &other) const;

    template <typename Con>
        requires ValidContainer<T, Con>
    bool operator!=(const Con &other) const;

    // Перегрузка оператора []
    T &operator[](int ind);
    const T &operator[](int ind) const;

    Vector<T> operator-(void);

#pragma endregion operators

#pragma region vector_methods
    // Векторная сумма
    template <ConvertAssignableSum<T> U>
    decltype(auto) vec_sum(const Vector<U> &other) const;
    template <ConvertAssignableSum<T> U>
    Vector<T> &vec_sum_eq(const Vector<U> &other);

    // Сложение вектора с числом
    template <ConvertAssignableSum<T> U>
    decltype(auto) plus(const U &num);
    template <ConvertAssignableSum<T> U>
    Vector<T> &plus_eq(const U &num);

    // Векторное вычитание
    template <ConvertAssignableSub<T> U>
    decltype(auto) vec_sub(const Vector<U> &other) const;
    template <ConvertAssignableSub<T> U>
    Vector<T> &vec_sub_eq(const Vector<U> &other);

    // Вычитание числа из вектора
    template <ConvertAssignableSub<T> U>
    decltype(auto) minus(const U &num) const;
    template <ConvertAssignableSub<T> U>
    Vector<T> &minus_eq(const U &num);

    // Поэлементное умножение
    template <ConvertAssignableMul<T> U>
    decltype(auto) vec_el_mul(const Vector<U> &other) const;
    template <ConvertAssignableMul<T> U>
    Vector<T> &vec_el_mul_eq(const Vector<U> &other);

    // Умножение вектора на число
    template <ConvertAssignableMul<T> U>
    decltype(auto) mul(const U &num) const;
    template <ConvertAssignableMul<T> U>
    Vector<T> &mul_eq(const U &num);

    // Поэлементное Деление
    template <ConvertAssignableDiv<T> U>
    decltype(auto) vec_el_div(const Vector<U> &other) const;
    template <ConvertAssignableDiv<T> U>
    Vector<T> &vec_el_div_eq(const Vector<U> &other);

    // Деление вектора на число
    template <ConvertAssignableDiv<T> U>
    decltype(auto) div(const U &num) const;
    template <ConvertAssignableDiv<T> U>
    Vector<T> &div_eq(const U &num);

    template <ConvertAssignableOperationable<T> U>
    decltype(auto) vec_mul(const Vector<U> &other) const;
    template <ConvertAssignableOperationable<T> U>
    Vector<T> &vec_mul_eq(const Vector<U> &other);

    template <ConvertAssignableOperationable<T> U>
    decltype(auto) scal_mul(const Vector<U> &other);

    template <typename Con>
        requires ValidContainer<T, Con>
    bool is_equal(const Con &other) const;

    void print(void) const;

    // отрицание вектора
    Vector<T> negative(void);

#pragma endregion vector_methods

    // TODO
    // RANDOM ACCESS ITERATOR
    // RANGES

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
