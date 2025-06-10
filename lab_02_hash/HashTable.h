#pragma once

#include <initializer_list>
#include <memory>
#include "concepts.h"
#include "base_hash_table.h"
#include "HashChain.h"
#include "HashIterator.hpp"
#include "ConstHashIterator.hpp"

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
class HashTable : public BaseHashTable
{
public:
#pragma region STLAliases
    using value_type = HashElem<K, V>;
    using size_type = size_t;
    using iterator = HashIterator<K, V, HashFunc>;
    using const_iterator = ConstHashIterator<K, V, HashFunc>;
#pragma endregion STLAliases

#pragma region 5Rule
    HashTable();
    HashTable(int new_capacity);
    HashTable(std::initializer_list<std::pair<K, V>> list_elems, int new_capacity);
    HashTable(const HashTable &og_hash);
    HashTable(HashTable &&og_hash);
    template <std::ranges::input_range R>
        requires std::convertible_to<std::ranges::range_value_t<R>, std::pair<K, V>>
    HashTable(R &&range);
    HashTable<K, V, HashFunc> operator=(const HashTable<K, V, HashFunc> &other_table);
    ~HashTable() = default;
#pragma endregion 5Rule

#pragma region ControlFuncs
    void insert_node(const K &key, const V &val);
    void insert_node(K &&key, V &&val);
    void insert_node(const HashElem<K, V> &elem);
    void insert_node(std::pair<K, V> &node);
    void insert_nodes(std::initializer_list<std::pair<K, V>> list_elems);
    void insert_nodes(std::initializer_list<HashElem<K, V>> list_elems);
    void delete_node(const K &key);
    void delete_node(K &&key);
    void delete_node(const HashElem<K, V> &elem);
    void delete_nodes(std::initializer_list<K> keys);
    bool contains(const K &key) const noexcept;
    bool contains(const K &&key) const noexcept;
    bool contains(const HashElem<K, V> &elem) const noexcept;
    bool contains(std::pair<K, V> &node) const noexcept;
    HashElem<K, V> &get_pair(const K &key) const;
    HashElem<K, V> &get_pair(K &&key) const;
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
    HashTable<K, V, HashFunc> &operator+(const std::pair<K, V> &pair);
    HashTable<K, V, HashFunc> &operator+(std::pair<K, V> &&pair);
    HashTable<K, V, HashFunc> &operator+(const HashElem<K, V> &elem);
    HashTable<K, V, HashFunc> &operator+(std::initializer_list<std::pair<K, V>> list);
    HashTable<K, V, HashFunc> &operator-(const K &key);
    HashTable<K, V, HashFunc> &operator-(K &&key);
    HashTable<K, V, HashFunc> &operator-(const HashElem<K, V> &elem);
    HashTable<K, V, HashFunc> &operator-(std::initializer_list<K> keys);
    bool operator==(const HashTable<K, V, HashFunc> &other) const noexcept;
    bool operator!=(const HashTable<K, V, HashFunc> &other) const noexcept;
#pragma endregion Operators

#pragma region OtherFuncs
    double calc_load_factor() const noexcept;
    bool empty() const noexcept override;
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

    std::shared_ptr<HashChain<K, V>> array;
    std::shared_ptr<size_t> mod_count;
};

// вывод через std::cout;
template <Key K, Value V, typename HashFunc>
std::ostream &operator<<(std::ostream &os, HashTable<K, V, HashFunc> &table)
{
    for (int i = 0; i < table.get_capacity(); i++)
    {
        os << "[" << i << "] -> " << table.get_list(i) << "\n";
    }
    return os;
}