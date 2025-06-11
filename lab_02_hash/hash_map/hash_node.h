#pragma once

#include <memory>
#include "concepts.h"

template <Key K, Value V>
class HashChain;

template <Key K, Value V>
class HashNode
{
    friend HashChain<K, V>;

public:
#pragma region constructors
    HashNode(const K &key, const V &val) noexcept;
    explicit HashNode(const HashNode<K, V> &other) noexcept;
    HashNode(HashNode<K, V> &&other) noexcept;
    HashNode(std::pair<K, V> &node) noexcept;
    ~HashNode() = default;
    HashNode<K, V> &operator=(const HashNode<K, V> &og_elem) noexcept;
    HashNode<K, V> &operator=(HashNode<K, V> &&og_elem) noexcept;
#pragma endregion constructors

#pragma region Operators
    bool operator==(const HashNode<K, V> &other) const noexcept;
    bool operator!=(const HashNode<K, V> &other) const noexcept;
    bool operator==(std::pair<K, V> &node) const noexcept;
    bool operator!=(std::pair<K, V> &node) const noexcept;
#pragma endregion Operators

#pragma region getters_setters
    K get_key() const noexcept;
    V get_val() const noexcept;
    void set_val(const V &val) noexcept;
    void set_val(V &&val) noexcept;

    std::shared_ptr<HashNode<K, V>> get_next() const noexcept;
    std::weak_ptr<HashNode<K, V>> get_prev() const noexcept;
    void set_next(std::shared_ptr<HashNode<K, V>> next_elem) noexcept;
    void set_prev(std::weak_ptr<HashNode<K, V>> prev_elem) noexcept;
#pragma endregion getters_setters

    bool has_next() const noexcept;
    bool has_prev() const noexcept;

private:
    K _key;
    V _val;
    std::shared_ptr<HashNode<K, V>> _next;
    std::weak_ptr<HashNode<K, V>> _prev;
};

template <Key K, Value V>
std::ostream &operator<<(std::ostream &os, HashNode<K, V> &elem);

#include "hash_node.hpp"