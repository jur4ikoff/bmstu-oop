#pragma once

#include <iostream>
#include <iterator>
#include <memory>

#include "vector_concepts.hpp"

template <ContainerType T>
class BaseReverseIterator
{
public:
#pragma region alias
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;

#pragma endregion alias

    BaseReverseIterator() = default;
    virtual ~BaseReverseIterator() = default;

    // Перегружаем * и ->
    const T &operator*() const;
    const T *operator->() const;

    // Перегружаем операторы == и !=
    bool operator==(const BaseReverseIterator<T> &other) const;
    bool operator!=(const BaseReverseIterator<T> &other) const;
    auto operator<=>(const BaseReverseIterator<T> &other) const;


    int get_size() const;
    int get_index() const;
    std::weak_ptr<T[]> get_piter() const;
protected:
    int size = 0;
    int index = 0;

    // Проверка, жив ли тот объект, на который указывает иттератор
    void check_vector(int line) const;

    // Проверка на то, что индекс в пределах размера объекта
    void check_iter(int line) const;

    // Проверка, что итераторы одного типа
    void check_same_iter_type(const BaseReverseIterator<T> &other, int line) const;

    // Возвращает иттератор по индексу
    T *get_ptr_cur() const;

    std::weak_ptr<T[]> piter;
};

#include "base_reverse_iterator.hpp"
