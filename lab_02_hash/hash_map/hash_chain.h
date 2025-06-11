#pragma once

#include <initializer_list>
#include <memory>
#include <iostream>
#include "concepts.h"
#include "hash_node.h"

template <Key K, Value V>
class HashChain
{
public:
#pragma region five_rule
    HashChain();
    HashChain(const HashChain<K, V> &other);
    HashChain(HashChain<K, V> &&other);
    HashChain(std::initializer_list<std::pair<K, V>> list_elems);
    ~HashChain() = default;

    HashChain<K, V> &operator=(const HashChain<K, V> &other);
    HashChain<K, V> &operator=(std::initializer_list<std::pair<K, V>> list_elems);
#pragma endregion five_rule

#pragma region Operators
    bool operator==(const HashChain<K, V> &other) const;
    bool operator!=(const HashChain<K, V> &other) const;
    bool operator==(std::initializer_list<std::pair<K, V>> list_elems) const;
    bool operator!=(std::initializer_list<std::pair<K, V>> list_elems) const;
#pragma endregion Operators

#pragma region OtherFuncs
    void insert_node(const K &key, const V &val);
    void insert_node(K &&key, V &&val);
    void insert_node(std::pair<K, V> &node);
    void delete_node(const K &key);
    void delete_node(K &&key);
    bool contains(const K &key);
    bool contains(K &&key);
    HashNode<K, V> &get_pair(const K &key) const;
    HashNode<K, V> &get_pair(K &&key) const;
    V &get_val(const K &key);
    V &get_val(K &&key);
    int get_count();
    std::shared_ptr<HashNode<K, V>> get_list();
    void clear() noexcept;
#pragma endregion OtherFuncs

private:
    void ckeck_size();

    std::shared_ptr<HashNode<K, V>> _list;
    size_t _count;
};

// вывод через std::cout;
template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, HashChain<K, V> &chain)
{
    if (chain.get_count() == 0)
    {
        os << "[NONE]";
        return os;
    }
    std::shared_ptr<HashNode<K, V>> current = chain.get_list();
    while (current)
    {
        os << *(current.get()) << " -> ";
        if (!current->has_next())
        {
            os << "[NONE]";
        }
        current = current->get_next();
    }
    return os;
}

#include "hash_chain.hpp"
