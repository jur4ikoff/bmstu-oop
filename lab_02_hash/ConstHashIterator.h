#ifndef CONSTHASHITERATOR_H
#define CONSTHASHITERATOR_H

#include <iterator>
#include <memory>
#include "concepts.h"
#include "BaseIterator.h"

template <ValidKey K, ValidValue V>
class HashElem;

template <ValidKey K, ValidValue V>
class HashChain;

template <ValidKey K, ValidValue V, typename HashFunc>
class ConstHashIterator: public BaseIterator
{
public:
#pragma region STLAliases
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const HashElem<K, V>;
    using difference_type = std::ptrdiff_t;
    using pointer = const HashElem<K, V> *;
    using reference = const HashElem<K, V> &;
#pragma endregion STLAliases

#pragma region 5Rule
    ConstHashIterator() = default;
    ConstHashIterator(std::shared_ptr<HashChain<K, V>> table, size_t index,
                 std::shared_ptr<HashElem<K, V>> current, std::shared_ptr<size_t> mod_count_og, size_t capacity);
    ConstHashIterator(const ConstHashIterator<K, V, HashFunc>& og_iter);
    ConstHashIterator(ConstHashIterator<K, V, HashFunc> &&og_iter);
    ~ConstHashIterator() = default;
    ConstHashIterator<K, V, HashFunc>& operator =(const ConstHashIterator<K, V, HashFunc>& other_iter);
#pragma endregion 5Rule

#pragma region Funcs
    void check_if_valid() const;
    size_t get_index() const override;
    size_t get_capacity() const override;
    size_t get_needed_mod_count() const;
#pragma endregion Funcs

#pragma region Operators
    reference operator*() const;
    pointer operator->() const;
    ConstHashIterator& operator++();
    ConstHashIterator& operator--();
    ConstHashIterator operator++(int);
    ConstHashIterator operator--(int);
    bool operator==(const ConstHashIterator &other) const noexcept;
    bool operator!=(const ConstHashIterator &other) const noexcept;
#pragma endregion Operators

private:
    std::weak_ptr<HashChain<K, V>> table;
    std::shared_ptr<HashElem<K, V>> current;
    std::shared_ptr<size_t> mod_count_ptr;
    size_t mod_count;
    size_t index;
    size_t capacity;
    void advance_to_valid();
};

#endif // CONSTHASHITERATOR_H
