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
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;

#pragma endregion alias

    BaseReverseIterator() = default;
    virtual ~BaseReverseIterator() = default;

    // Перегружаем * и ->
    const_reference operator*() const;
    const_pointer operator->() const;

    // Перегружаем операторы == и !=
    bool operator==(const BaseReverseIterator<T> &other) const noexcept;
    bool operator!=(const BaseReverseIterator<T> &other) const noexcept;
    auto operator<=>(const BaseReverseIterator<T> &other) const noexcept;
    explicit operator bool() const noexcept;

protected:
  
    void check_vector(int line) const;   // Проверка, жив ли тот объект, на который указывает иттератор
    void check_iter(int line) const; // Проверка на то, что индекс в пределах размера контенера

    // Возвращает иттератор по индексу
    pointer get_ptr_cur() const;

    std::weak_ptr<T[]> piter;
    int size = 0;
    int index = 0;
};

#include "base_reverse_iterator.hpp"
