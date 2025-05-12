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
    using reference = T &;
    using const_reference = const T &;

    using pointer = T *;
    using const_pointer = const T *;

#pragma endregion alias

    BaseIterator() = default;
    virtual ~BaseIterator() = default;

    // Перегружаем * и ->
    const_reference operator*() const;
    const_pointer operator->() const;

    // Перегружаем операторы == и !=
    bool operator==(const BaseIterator<T> &other) const noexcept;
    bool operator!=(const BaseIterator<T> &other) const noexcept;
    auto operator<=>(const BaseIterator<T> &other) const noexcept;


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
    pointer get_ptr_cur() const;
    std::weak_ptr<T[]> piter;
};

#include "base_iterator.hpp"
