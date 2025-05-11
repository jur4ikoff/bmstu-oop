#pragma once

#include <iostream>
#include <iterator>
#include <memory>

#include "vector_concepts.hpp"

template <ContainerType T>
class BaseIterator
{
public:
#pragma region alias
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using const_point = const T *;
    using reference = T &;

#pragma endregion alias

    BaseIterator() = default;
    virtual ~BaseIterator() = default;

    // Перегружаем * и ->
    const T &operator*() const;
    const T *operator->() const;

    // Перегружаем операторы == и !=
    bool operator==(const BaseIterator<T> &other) const;
    bool operator!=(const BaseIterator<T> &other) const;
    auto operator<=>(const BaseIterator<T> &other) const;

protected:
    size_t size = 0;
    size_t index = 0;

    // Проверка, жив ли тот объект, на который указывает иттератор
    void check_vector(int line) const;

    // Проверка на то, что индекс в пределах размера объекта
    void check_iter(int line) const;

    // Проверка, что итераторы одного типа
    void check_same_iter_type(const BaseIterator<T> &other, int line) const;

    // Возвращает иттератор по индексу
    T *get_ptr_cur() const;

    std::weak_ptr<T[]> piter;
};

#include "base_iterator.hpp"
