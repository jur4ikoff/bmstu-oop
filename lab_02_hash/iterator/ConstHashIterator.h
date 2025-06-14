#ifndef CONSTHASHITERATOR_H
#define CONSTHASHITERATOR_H

#include "BaseIterator.h"
#include "concepts.h"
#include <iterator>
#include <memory>

template <Key K, Value V>
class HashNode;

template <Key K, Value V>
class HashChain;

template <Key K, Value V, typename HashFunc>
class ConstHashIterator : public BaseIterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = const HashNode<K, V>;
    using difference_type = std::ptrdiff_t;
    using pointer = const HashNode<K, V> *;
    using reference = const HashNode<K, V> &;

#pragma region 5Rule
    ConstHashIterator() = default;
    ConstHashIterator(std::shared_ptr<HashChain<K, V>> table, size_t index,
                      std::shared_ptr<HashNode<K, V>> current, size_t capacity);
    ConstHashIterator(const ConstHashIterator<K, V, HashFunc> &og_iter);
    ConstHashIterator(ConstHashIterator<K, V, HashFunc> &&og_iter);
    ~ConstHashIterator() = default;
    ConstHashIterator<K, V, HashFunc> &operator=(const ConstHashIterator<K, V, HashFunc> &other_iter);
#pragma endregion 5Rule

#pragma region Funcs
    void check_if_valid() const;
    size_t get_index() const override;
    size_t get_capacity() const override;
#pragma endregion Funcs

#pragma region Operators
    reference operator*() const;
    pointer operator->() const;
    ConstHashIterator &operator++();
    ConstHashIterator &operator--();
    ConstHashIterator operator++(int);
    ConstHashIterator operator--(int);
    bool operator==(const ConstHashIterator &other) const noexcept;
    bool operator!=(const ConstHashIterator &other) const noexcept;
#pragma endregion Operators

private:
    std::weak_ptr<HashChain<K, V>> table;
    std::shared_ptr<HashNode<K, V>> current;
    size_t index;
    size_t capacity;
    void advance_to_valid();
};

#endif // CONSTHASHITERATOR_H
