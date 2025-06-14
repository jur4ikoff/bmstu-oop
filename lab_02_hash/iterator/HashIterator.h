#ifndef HASHITERATOR_H
#define HASHITERATOR_H

#include "BaseIterator.h"
#include "concepts.h"
#include <iterator>
#include <memory>

template <Key K, Value V>
class HashNode;

template <Key K, Value V>
class HashChain;

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
class HashIterator : public BaseIterator
{
public:
#pragma region STLAliases
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = HashNode<K, V>;
    using difference_type = std::ptrdiff_t;
    using pointer = HashNode<K, V> *;
    using reference = HashNode<K, V> &;
#pragma endregion STLAliases

#pragma region 5Rule
    HashIterator() = default;
    HashIterator(std::shared_ptr<HashChain<K, V>> table, size_t index,
                 std::shared_ptr<HashNode<K, V>> current, size_t capacity);
    HashIterator(const HashIterator<K, V, HashFunc> &og_iter);
    HashIterator(HashIterator<K, V, HashFunc> &&og_iter);
    ~HashIterator() = default;
    HashIterator<K, V, HashFunc> &operator=(const HashIterator<K, V, HashFunc> &other_iter);
#pragma endregion 5Rule

#pragma region Funcs
    void check_if_valid() const;
    size_t get_index() const override;
    size_t get_capacity() const override;
#pragma endregion Funcs

#pragma region Operators
    reference operator*() const;
    pointer operator->() const;
    HashIterator &operator++();
    HashIterator &operator--();
    HashIterator operator++(int);
    HashIterator operator--(int);
    bool operator==(const HashIterator &other) const noexcept;
    bool operator!=(const HashIterator &other) const noexcept;
#pragma endregion Operators
private:
    std::weak_ptr<HashChain<K, V>> table;
    std::shared_ptr<HashNode<K, V>> current;

    size_t index;
    size_t capacity;
    void advance_to_valid();
};

#endif // HASHITERATOR_H
