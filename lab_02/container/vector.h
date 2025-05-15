#pragma once

#include "base_container.h"
#include "vector_concepts.hpp"
#include "vector_const_iterator.h"
#include "vector_const_reverse_iterator.h"
#include "vector_iterator.h"
#include "vector_reverse_iterator.h"

#include <iostream>
#include <memory>

template <ContainerType T>
class Vector : public baseContainer
{
public:
#pragma region aliases
    using value_type = T;

    using reference = T &;
    using const_reference = const T &;

    using iterator = VectorIterator<T>;
    using const_iterator = VectorConstIterator<T>;
    using reverse_iterator = VectorReverseIterator<T>;
    using const_reverse_iterator = VectorConstReverseIterator<T>;
#pragma endregion aliases

    friend class VectorIterator<T>;
    friend class VectorConstIterator<T>;
    friend class VectorReverseIterator<T>;
    friend class VectorConstReverseIterator<T>;

#pragma region Constructors
    Vector();                                // Обычный конструктор
    explicit Vector(const Vector<T> &other); // Конструктор копирования
    Vector(Vector<T> &&other) noexcept;      // Копирование по правой ссылке на вектор этого же типа
    template <typename U>
        requires ConvertAssignable<T, U>
    explicit Vector(const Vector<U> &other); // Преобразование из вектора другого типа
    template <typename Con>
        requires ValidContainer<T, Con>
    explicit Vector(const Con &other);              // Преобразование из контейнера, подходящего под требования
    explicit Vector(baseContainer::size_type size); // Конструктор по рамзеру
    template <ConvertAssignable<T> U>
    Vector(std::initializer_list<U> arr); // Конструктор по списку иницалиизации
    template <ConvertAssignable<T> U>
    Vector(baseContainer::size_type size, const U *arr); // Конструктор по размеру и массиву заполнения
    template <ConvertAssignable<T> U>
    Vector(baseContainer::size_type size, const U &elem, ...); // Конструктор по длине и параметрам, для заполнения
    template <CompatibleIterator<T> U>
    Vector(U begin, U end); // Конструктор по иттератору на некий контейнер, на начало и конец

    template <typename I, typename S>
        requires CompatibleIterator<I, T> && SentinelIter<S, I>
    Vector(I beg, S end);

    ~Vector() = default;
#pragma endregion Constructors

#pragma region asign
    // перегрузка оператора равно
    template <ConvertAssignable<T> U>
    Vector<T> &operator=(const std::initializer_list<U> &arr);
    template <ValidContainer<T> Con>
    Vector<T> &operator=(const Con &other);
    template <ValidContainer<T> Con>
    Vector<T> &operator=(Con &&other) noexcept;
    template <ConvertAssignable<T> U>
    Vector<T> &operator=(const Vector<U> &other);
    template <ConvertAssignable<T> U>
    Vector<T> &operator=(Vector<U> &&other) noexcept;

    template <ValidContainer<T> Con>
    bool is_equal(const Con &other) const;
    template <ConvertAssignable<T> U>
    bool is_equal(const Vector<U> &other) const;
#pragma endregion asign

#pragma region sum
    // Перегрузка +
    // Перегрузка оператора + для вектора
    template <ValidContainer<T> Con>
    decltype(auto) operator+(const Con &other) const;
    template <ConvertAssignableSum<T> U>
    decltype(auto) operator+(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    Vector<T> &operator+=(const Con &other);
    template <ConvertAssignableSum<T> U>
    Vector<T> &operator+=(const Vector<U> &other);
    template <ConvertAssignable<T> U>
    Vector<T> &operator+=(std::initializer_list<U> arr);
    template <ValidContainer<T> Con>
    decltype(auto) vec_sum(const Con &other) const;
    template <ConvertAssignableSum<T> U>
    decltype(auto) vec_sum(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    Vector<T> &vec_sum_eq(const Con &other);
    template <ConvertAssignableSum<T> U>
    Vector<T> &vec_sum_eq(const Vector<U> &other);

    // Сложение вектора и числа
    template <ConvertAssignableSum<T> U>
    decltype(auto) operator+(const U &num) const;
    template <ConvertAssignableSum<T> U>
    Vector<T> &operator+=(const U &num);
    // Сложение вектора с числом
    template <ConvertAssignableSum<T> U>
    decltype(auto) plus(const U &num);
    template <ConvertAssignableSum<T> U>
    Vector<T> &plus_eq(const U &num);
#pragma endregion sum

#pragma region sub
    // Перегрузка -
    // Перегрузка оператора - для вектора
    template <ValidContainer<T> Con>
    decltype(auto) operator-(const Con &other) const;
    template <ConvertAssignableSub<T> U>
    decltype(auto) operator-(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    Vector<T> &operator-=(const Con &other);
    template <ConvertAssignableSub<T> U>
    Vector<T> &operator-=(const Vector<U> &other);
    template <ConvertAssignable<T> U>
    Vector<T> &operator-=(std::initializer_list<U> arr);
    template <ValidContainer<T> Con>
    decltype(auto) vec_sub(const Con &other) const;
    template <ConvertAssignableSub<T> U>
    decltype(auto) vec_sub(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    Vector<T> &vec_sub_eq(const Con &other);
    template <ConvertAssignableSub<T> U>
    Vector<T> &vec_sub_eq(const Vector<U> &other);

    // Перегрзука оператора - для числа
    template <ConvertAssignableSub<T> U>
    decltype(auto) operator-(const U &num) const;
    template <ConvertAssignableSub<T> U>
    Vector<T> &operator-=(const U &num);
    // Вычитание числа из вектора
    template <ConvertAssignableSub<T> U>
    decltype(auto) minus(const U &num) const;
    template <ConvertAssignableSub<T> U>
    Vector<T> &minus_eq(const U &num);

    Vector<T> operator-(void); // Оператор отрицание
    Vector<T> negative(void);  // отрицание вектора
#pragma endregion

#pragma region mul
    // Перегрузка *
    // Перегрузка оператора умножения для вектора
    template <ValidContainer<T> Con>
    decltype(auto) operator*(const Con &other) const;
    template <ConvertAssignableMul<T> U>
    decltype(auto) operator*(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    Vector<T> &operator*=(const Con &other);
    template <ConvertAssignableMul<T> U>
    Vector<T> &operator*=(const Vector<U> &other);
    template <ConvertAssignable<T> U>
    Vector<T> &operator*=(std::initializer_list<U> arr);
    // Поэлементное умножение
    template <ValidContainer<T> Con>
    decltype(auto) vec_el_mul(const Con &other) const;
    template <ConvertAssignableMul<T> U>
    decltype(auto) vec_el_mul(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    Vector<T> &vec_el_mul_eq(const Con &other);
    template <ConvertAssignableMul<T> U>
    Vector<T> &vec_el_mul_eq(const Vector<U> &other);

    // Перегрзука оператора * для числа
    template <ConvertAssignableMul<T> U>
    decltype(auto) operator*(const U &num) const;
    template <ConvertAssignableMul<T> U>
    Vector<T> &operator*=(const U &num);
    // Умножение вектора на число
    template <ConvertAssignableMul<T> U>
    decltype(auto) mul(const U &num) const;
    template <ConvertAssignableMul<T> U>
    Vector<T> &mul_eq(const U &num);
#pragma endregion mul

#pragma region div
    // Перегрузка /
    // Перегрузка оператора /. Поэлементное деление вектора на вектор
    template <ValidContainer<T> Con>
    decltype(auto) operator/(const Con &other) const;
    template <ConvertAssignableDiv<T> U>
    decltype(auto) operator/(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    Vector<T> &operator/=(const Con &other);
    template <ConvertAssignableDiv<T> U>
    Vector<T> &operator/=(const Vector<U> &other);
    template <ConvertAssignable<T> U>
    Vector<T> &operator/=(std::initializer_list<U> arr);
    // Поэлементное Деление
    template <ValidContainer<T> Con>
    decltype(auto) vec_el_div(const Con &other) const;
    template <ConvertAssignableDiv<T> U>
    decltype(auto) vec_el_div(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    Vector<T> &vec_el_div_eq(const Con &other);
    template <ConvertAssignableDiv<T> U>
    Vector<T> &vec_el_div_eq(const Vector<U> &other);

    // Перегрузка оператора / деление на число
    template <ConvertAssignableDiv<T> U>
    decltype(auto) operator/(const U &num) const;
    template <ConvertAssignableDiv<T> U>
    Vector<T> &operator/=(const U &num);
    // Деление вектора на число
    template <ConvertAssignableDiv<T> U>
    decltype(auto) div(const U &num) const;
    template <ConvertAssignableDiv<T> U>
    Vector<T> &div_eq(const U &num);
#pragma endregion div

#pragma region vector_scalar_mul
    // векторное умножение
    template <ValidContainer<T> Con>
    decltype(auto) operator^(const Con &other) const;
    template <ConvertAssignableOperationable<T> U>
    decltype(auto) operator^(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    Vector<T> &operator^=(const Con &other);
    template <ConvertAssignableOperationable<T> U>
    Vector<T> &operator^=(const Vector<U> &other);
    template <ConvertAssignable<T> U>
    Vector<T> &operator^=(std::initializer_list<U> arr);
    template <ValidContainer<T> Con>
    decltype(auto) vec_mul(const Con &other) const;
    template <ConvertAssignableOperationable<T> U>
    decltype(auto) vec_mul(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    Vector<T> &vec_mul_eq(const Con &other);
    template <ConvertAssignableOperationable<T> U>
    Vector<T> &vec_mul_eq(const Vector<U> &other);

    // перегрузка оператора & - Скалярное умножение
    template <ValidContainer<T> Con>
    decltype(auto) operator&(const Con &other) const;
    template <ConvertAssignableOperationable<T> U>
    decltype(auto) operator&(const Vector<U> &other) const;
    template <ValidContainer<T> Con>
    decltype(auto) scal_mul(const Con &other);
    template <ConvertAssignableOperationable<T> U>
    decltype(auto) scal_mul(const Vector<U> &other);
#pragma endregion vector_scalar_mul

#pragma region equals
    // перегрузка равенства и неравенства
    template <ValidContainer<T> Con>
    bool operator==(const Con &other) const;
    template <ValidContainer<T> Con>
    bool operator!=(const Con &other) const;
    template <ConvertAssignable<T> U>
    bool operator==(const Vector<T> &other) const;
    template <ConvertAssignable<T> U>
    bool operator==(std::initializer_list<U> arr) const;
    template <ConvertAssignable<T> U>
    bool operator!=(const Vector<T> &other) const;
#pragma endregion equals

#pragma region setters_and_getters
    // Перегрузка оператора []
    reference operator[](int index);
    const_reference operator[](int index) const;

    template <ConvertAssignable<T> U>
    void set_item(int index, const U &elem);
    reference get_item(int index);
    const_reference get_item(int index) const;

#pragma endregion setters_and_getters

#pragma region methods
    decltype(auto) len() const;           // Функция возвращает математическую длину вектора
    decltype(auto) normalization() const; // Функция нормализует вектор
    bool is_normalize() const;            // Функция проверяет нормализован ли вектор
    bool is_zero() const;                 // Функция проверяет нулевой ли вектор

    template <ConvertAssignable<T> U>
    decltype(auto) calc_angle(const Vector<U> &other) const; // Функция считает угол между двумя векторами
    template <ConvertAssignable<T> U>
    bool is_colliniar(const Vector<U> &other) const; // Проверка на коллинеарность векторов
    template <ConvertAssignable<T> U>
    bool is_orthogonal(const Vector<U> &other) const; // Проверка на ортогональность векторов

    void print(void) const; // Вывод вектора в консоль
#pragma endregion methods

#pragma region iterators
    // Возвращает обычный итератор на начало/конец вектораы
    VectorIterator<T> begin(void);
    VectorIterator<T> end(void);

    VectorConstIterator<T> begin(void) const;
    VectorConstIterator<T> end(void) const;

    // Возвращает константный интератор на начало/кенец вектора
    VectorConstIterator<T> cbegin(void) const;
    VectorConstIterator<T> cend(void) const;

    // Возвращает реверс интератор на начало/кенец вектора
    VectorReverseIterator<T> rbegin(void);
    VectorReverseIterator<T> rend(void);

    // Возвращает реверс интератор на начало/кенец вектора
    VectorConstReverseIterator<T> rbegin(void) const;
    VectorConstReverseIterator<T> rend(void) const;

    // Возвращает константный реверс интератор на начало/кенец вектора
    VectorConstReverseIterator<T> crbegin(void) const;
    VectorConstReverseIterator<T> crend(void) const;
#pragma endregion iterators

protected:
    void memory_allocation(const int &container_size, int line);

    template <typename U>
    void check_division_zero(const U &num, int line) const;                // Проверка деления num / 0
    void check_vector_size(baseContainer::size_type size, int line) const; // Проверка размера массива
    void check_arr_null(const T *arr, int line) const;                     // Проверка указателя на валидность
    void check_index(int index, int line) const;                           // Проверка индекса
    void check_size_equal(baseContainer::size_type size, int line) const;  // Проверка равенства двух размеров

private:
    std::shared_ptr<T[]> container;
};

#include "vector.hpp"
