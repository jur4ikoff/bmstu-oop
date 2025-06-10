#ifndef HASHCHAIN_H
#define HASHCHAIN_H

#include <initializer_list>
#include <memory>
#include <iostream>
#include "concepts.h"
#include "HashElem.h"

template <Key K, Value V>
class HashElem;

template <Key K, Value V>
class HashChain
{
public:
#pragma region Constructors
    HashChain();
    HashChain(const HashChain<K, V> &og_chain);
    HashChain(HashChain<K, V> &&og_chain);
    HashChain(std::initializer_list<std::pair<K, V>> list_elems);
    ~HashChain() = default;
#pragma endregion Constructors

#pragma region 5Rule
    HashChain<K, V> &operator=(const HashChain<K, V> &og_chain);
    HashChain<K, V> &operator=(std::initializer_list<std::pair<K, V>> list_elems);
#pragma endregion 5Rule

#pragma region Operators
    bool operator==(const HashChain<K, V> &other_chain) const;
    bool operator!=(const HashChain<K, V> &other_chain) const;
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
    HashElem<K, V> &get_pair(const K &key) const;
    HashElem<K, V> &get_pair(K &&key) const;
    V &get_val(const K &key);
    V &get_val(K &&key);
    int get_count();
    std::shared_ptr<HashElem<K, V>> get_list();
    void clear() noexcept;
#pragma endregion OtherFuncs
private:
    std::shared_ptr<HashElem<K, V>> list;
    size_t count;
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
    std::shared_ptr<HashElem<K, V>> current = chain.get_list();
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

#endif // HASHCHAIN_H
