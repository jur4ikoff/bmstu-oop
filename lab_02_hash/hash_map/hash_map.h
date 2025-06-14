#pragma once

#include "ConstHashIterator.hpp"
#include "HashIterator.hpp"
#include "base_hash_map.h"
#include "concepts.h"
#include "hash_chain.h"
#include <initializer_list>
#include <memory>

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
class HashMap : public BaseHashMap
{
public:
#pragma region aliases
    using value_type = HashNode<K, V>;
    using size_type = size_t;

    using reference = value_type &;
    using const_reference = const value_type &;

    using iterator = HashIterator<K, V, HashFunc>;
    using const_iterator = ConstHashIterator<K, V, HashFunc>;
#pragma endregion aliases

#pragma region five_rule
    HashMap();
    HashMap(int capacity);
    HashMap(std::initializer_list<std::pair<K, V>> list_elems, int new_capacity);
    HashMap(const HashMap &og_hash);
    HashMap(HashMap &&og_hash);
    template <std::ranges::input_range R>
        requires std::convertible_to<std::ranges::range_value_t<R>, std::pair<K, V>>
    HashMap(R &&range);
    HashMap<K, V, HashFunc> operator=(const HashMap<K, V, HashFunc> &other_table);
    ~HashMap() = default;
#pragma endregion five_rule

#pragma region ControlFuncs
    void insert_node(const K &key, const V &val);
    void insert_node(K &&key, V &&val);
    void insert_node(const HashNode<K, V> &elem);
    void insert_node(std::pair<K, V> &node);
    void insert_nodes(std::initializer_list<std::pair<K, V>> list_elems);
    void insert_nodes(std::initializer_list<HashNode<K, V>> list_elems);
    void delete_node(const K &key);
    void delete_node(K &&key);
    void delete_node(const HashNode<K, V> &elem);
    void delete_nodes(std::initializer_list<K> keys);
    bool contains(const K &key) const noexcept;
    bool contains(const K &&key) const noexcept;
    bool contains(const HashNode<K, V> &elem) const noexcept;
    bool contains(std::pair<K, V> &node) const noexcept;
    HashNode<K, V> &get_pair(const K &key) const;
    HashNode<K, V> &get_pair(K &&key) const;
    V &get_val(const K &key) const noexcept;
    V &get_val(K &&key) const noexcept;
    HashChain<K, V> &get_list(const int index) const;
    void clear() noexcept;
#pragma endregion ControlFuncs

#pragma region Operators
    V &operator[](const K &key);
    const V &operator[](const K &key) const;
    V &operator[](K &&key);
    const V &operator[](K &&key) const;
    HashMap<K, V, HashFunc> &operator+(const std::pair<K, V> &pair);
    HashMap<K, V, HashFunc> &operator+(std::pair<K, V> &&pair);
    HashMap<K, V, HashFunc> &operator+(const HashNode<K, V> &elem);
    HashMap<K, V, HashFunc> &operator+(std::initializer_list<std::pair<K, V>> list);
    HashMap<K, V, HashFunc> &operator-(const K &key);
    HashMap<K, V, HashFunc> &operator-(K &&key);
    HashMap<K, V, HashFunc> &operator-(const HashNode<K, V> &elem);
    HashMap<K, V, HashFunc> &operator-(std::initializer_list<K> keys);
    bool operator==(const HashMap<K, V, HashFunc> &other) const noexcept;
    bool operator!=(const HashMap<K, V, HashFunc> &other) const noexcept;
#pragma endregion Operators

#pragma region OtherFuncs
    double calc_load_factor() const noexcept;
    bool is_empty() const noexcept override;
    size_t get_mod_count() const noexcept;
    size_t get_capacity() const noexcept override;
    size_t get_count() const noexcept override;
    size_t size() const noexcept override;

    HashIterator<K, V, HashFunc> begin() noexcept;
    HashIterator<K, V, HashFunc> end() noexcept;
    ConstHashIterator<K, V, HashFunc> begin() const noexcept;
    ConstHashIterator<K, V, HashFunc> end() const noexcept;
    ConstHashIterator<K, V, HashFunc> cbegin() const noexcept;
    ConstHashIterator<K, V, HashFunc> cend() const noexcept;
#pragma endregion OtherFuncs

protected:
    void memory_allocation(int count);
    void rehash();

private:
    void check_capacity(const size_type capacity) const;
    void check_index(const int index) const;

    std::shared_ptr<HashChain<K, V>> _array;
    std::shared_ptr<size_t> _mod_count;
};

// вывод через std::cout;
template <Key K, Value V, typename HashFunc>
std::ostream &operator<<(std::ostream &os, HashMap<K, V, HashFunc> &table);

#include "hash_map.hpp"
