#pragma once

#include "concepts.h"
#include "hash_node.h"
#include <initializer_list>
#include <iostream>
#include <memory>

template <Key K, Value V>
class HashChain
{
public:
#pragma region five_rule
    HashChain();
    explicit HashChain(const HashChain<K, V> &other);
    explicit HashChain(HashChain<K, V> &&other);
    explicit HashChain(std::initializer_list<std::pair<K, V>> list_elems);
    ~HashChain() = default;

    HashChain<K, V> &operator=(const HashChain<K, V> &other);
    HashChain<K, V> &operator=(std::initializer_list<std::pair<K, V>> list_elems);
#pragma endregion five_rule

#pragma region operators
    bool operator==(const HashChain<K, V> &other) const noexcept;
    bool operator==(std::initializer_list<std::pair<K, V>> list_elems) const noexcept;
    bool operator!=(const HashChain<K, V> &other) const noexcept;
    bool operator!=(std::initializer_list<std::pair<K, V>> list_elems) const noexcept;
#pragma endregion operators

#pragma region other
    bool is_contain(const K &key) noexcept;
    bool is_contain(K &&key) noexcept;

    void insert_node(const K &key, const V &val) noexcept;
    void insert_node(K &&key, V &&val) noexcept;
    void insert_node(std::pair<K, V> &node) noexcept;
    void delete_node(const K &key);
    void delete_node(K &&key);

    HashNode<K, V> &get_pair(const K &key) const;
    HashNode<K, V> &get_pair(K &&key) const;
    V &get_val(const K &key);
    V &get_val(K &&key);
    int get_count() noexcept;
    std::shared_ptr<HashNode<K, V>> get_list() noexcept;
    void clear() noexcept;

#pragma endregion other

private:
    void check_size();

    std::shared_ptr<HashNode<K, V>> _list;
    size_t _count;
};

// вывод через std::cout;
template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, HashChain<K, V> &chain);

#include "hash_chain.hpp"
