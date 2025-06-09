#include "HashTable.h"
#include "Errors.h"
#include <iostream>

#pragma region 5Rule
template <ValidKey K, ValidValue V, typename HashFunc>
requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>::HashTable()
{
  capacity = 1;
  alloc_mem(capacity);
}

template <ValidKey K, ValidValue V, typename HashFunc>
requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>::HashTable(int new_capacity)
{
  if (new_capacity <= 0)
  {
    throw BadCapacityError(__FILE__, typeid(*this).name(), __LINE__);
  }
  capacity = new_capacity;
  mod_count = 0;
  alloc_mem(capacity);
}

template <ValidKey K, ValidValue V, typename HashFunc>
requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>::HashTable(std::initializer_list<std::pair<K, V>> list_elems, int new_capacity) {
    if (new_capacity <= 0)
    {
        throw BadCapacityError(__FILE__, typeid(*this).name(), __LINE__);
    }
    capacity = new_capacity;
    mod_count = 0;
    alloc_mem(capacity);
    for (auto one_pair : list_elems) {
        insert_node(one_pair);
    }
}

template <ValidKey K, ValidValue V, typename HashFunc>
requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>::HashTable(const HashTable &og_hash)
{
  capacity = og_hash.capacity;
  alloc_mem(capacity);
  *(mod_count) = *(og_hash.mod_count);
  for (int i = 0; i < capacity; i++)
  {
    array.get()[i] = og_hash.array.get()[i];
  }
}

template <ValidKey K, ValidValue V, typename HashFunc>
requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>::HashTable(HashTable &&og_hash)
{
  capacity = og_hash.capacity;
  mod_count = std::move(og_hash.mod_count);
  array = std::move(og_hash.array);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc> HashTable<K, V, HashFunc>::operator=(const HashTable<K, V, HashFunc> &other_table)
{
  if (this == &other_table)
    return *this;
  capacity = other_table.capacity;
  alloc_mem(capacity);
  *(mod_count) = *(other_table.mod_count);
  for (int i = 0; i < capacity; i++)
  {
    array.get()[i] = other_table.array.get()[i];
  }
  (*mod_count)++;
  return (*this);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
template <std::ranges::input_range R>
requires std::convertible_to<std::ranges::range_value_t<R>, std::pair<K, V>>
HashTable<K, V, HashFunc>::HashTable(R&& range) {
    for (const auto& elem : range) {
        insert_node(elem.first, elem.second);
    }
}

#pragma endregion 5Rule

#pragma region Operators
template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
V &HashTable<K, V, HashFunc>::operator[](const K &key)
{
  return get_val(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
const V &HashTable<K, V, HashFunc>::operator[](const K &key) const
{
  return get_val(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
V &HashTable<K, V, HashFunc>::operator[](K &&key)
{
  return get_val(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
const V &HashTable<K, V, HashFunc>::operator[](K &&key) const
{
  return get_val(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::operator==(const HashTable<K, V, HashFunc> &other) const noexcept
{
  if (capacity != other.capacity || get_count() != other.get_count())
  {
    return false;
  }
  for (int i = 0; i < capacity; i++)
  {
    if (*(array.get()[i]) != *(other.array.get()[i]))
      return false;
  }
  return true;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::operator!=(const HashTable<K, V, HashFunc> &other) const noexcept
{
  return !((*this) == other);
}

// Операторы добавления
template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>& HashTable<K, V, HashFunc>::operator+(const std::pair<K, V>& pair) {
    insert_node(pair.first, pair.second);
    return *this;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>& HashTable<K, V, HashFunc>::operator+(std::pair<K, V>&& pair) {
    insert_node(std::move(pair.first), std::move(pair.second));
    return *this;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>& HashTable<K, V, HashFunc>::operator+(const HashElem<K, V>& elem) {
    insert_node(elem);
    return *this;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>& HashTable<K, V, HashFunc>::operator+(
    std::initializer_list<std::pair<K, V>> list
    ) {
    insert_nodes(list);
    return *this;
}

// Операторы удаления
template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>& HashTable<K, V, HashFunc>::operator-(const K& key) {
    delete_node(key);
    return *this;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>& HashTable<K, V, HashFunc>::operator-(K&& key) {
    delete_node(std::move(key));
    return *this;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>& HashTable<K, V, HashFunc>::operator-(const HashElem<K, V>& elem) {
    delete_node(elem);
    return *this;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>& HashTable<K, V, HashFunc>::operator-(
    std::initializer_list<K> keys
    ) {
    for (const auto& key : keys) {
        delete_node(key);
    }
    return *this;
}
#pragma endregion Operators

#pragma region OtherFuncs
template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
double HashTable<K, V, HashFunc>::calc_load_factor() const noexcept
{
  return (double)get_count() / (double)capacity;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::empty() const noexcept
{
  return get_count() == 0;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
size_t HashTable<K, V, HashFunc>::get_mod_count() const noexcept
{
  return *mod_count;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
size_t HashTable<K, V, HashFunc>::get_capacity() const noexcept
{
  return capacity;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
size_t HashTable<K, V, HashFunc>::get_count() const noexcept
{
  int total_count = 0;
  for (int i = 0; i < capacity; i++)
  {
    auto &current_chain = array.get()[i];
    total_count += current_chain.get_count();
  }
  return total_count;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
size_t HashTable<K, V, HashFunc>::size() const noexcept
{
  return get_count();
}

#pragma endregion OtherFuncs

#pragma region ControlFuncs
template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_node(const K &key, const V &val)
{
  size_t arr_index = HashFunc{}(key, capacity);
  array.get()[arr_index].insert_node(key, val);
  if (calc_load_factor() > 1.2)
  {
    rehash();
  }
  else
  {
    (*mod_count)++;
  }
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_node(K &&key, V &&val)
{
  insert_node(key, val);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_node(const HashElem<K, V> &elem)
{
  insert_node(elem.get_key(), elem.get_val());
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_node(std::pair<K, V> &node) {
    insert_node(node.first, node.second);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_nodes(std::initializer_list<std::pair<K, V>> list_elems) {
    for (auto elem : list_elems) {
        insert_node(elem);
    }
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_nodes(std::initializer_list<HashElem<K, V>> list_elems) {
    for (auto elem : list_elems) {
        insert_node(elem);
    }
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::delete_node(const K &key)
{
  size_t arr_index = HashFunc{}(key, capacity);
  (*mod_count)++;
  array.get()[arr_index].delete_node(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::delete_node(K &&key)
{
  delete_node(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::delete_node(const HashElem<K, V> &elem)
{
  delete_node(elem.get_key());
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::delete_nodes(std::initializer_list<K> keys)
{
    for (auto key : keys) {
        delete_node(key);
    }
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::contains(const K &key) const noexcept
{
  size_t arr_index = HashFunc(key, capacity);
  return array.get()[arr_index].contains(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::contains(const K &&key) const noexcept
{
  return contains(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::contains(const HashElem<K, V> &elem) const noexcept
{
  return contains(elem.get_key());
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::contains(std::pair<K, V> &node) const noexcept
{
    return contains(node.first);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashElem<K, V>& HashTable<K, V, HashFunc>::get_pair(const K& key) const {
    for (int i = 0; i < capacity; i++) {
        if (array.get()[i].contains(key)) {
            return array.get()[i].get_pair(key);
        }
    }
    throw KeyNotFoundError(__FILE__, typeid(*this).name(), __LINE__);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashElem<K, V>& HashTable<K, V, HashFunc>::get_pair(K&& key) const {
    return get_pair(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
V &HashTable<K, V, HashFunc>::get_val(const K &key) const noexcept
{
  size_t arr_index = HashFunc(key, capacity);
  return array.get()[arr_index].get_val(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
V &HashTable<K, V, HashFunc>::get_val(K &&key) const noexcept
{
  return get_val(key);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashChain<K, V> &HashTable<K, V, HashFunc>::get_list(const int index) const
{
  if (index >= capacity || index < 0)
  {
    throw TableIndexOutOfRange(__FILE__, typeid(*this).name(), __LINE__);
  }
  return array.get()[index];
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::clear() noexcept
{
  (*mod_count)++;
  for (int i = 0; i < capacity; i++)
  {
    array.get()[i].clear();
  }
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::begin() noexcept
{
  size_t idx = 0;
  while (idx < capacity)
  {
    auto &chain = array.get()[idx];
    auto first = chain.get_list();
    if (first)
    {
      return HashIterator<K, V, HashFunc>(
            array, idx, first, mod_count, capacity);
    }
    ++idx;
  }
  return end();
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::end() noexcept
{
  return HashIterator<K, V, HashFunc>(
    array, capacity, std::shared_ptr<HashElem<K, V>>{}, mod_count, capacity);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
ConstHashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::begin() const noexcept {
    size_t idx = 0;
    while (idx < capacity)
    {
        auto &chain = array.get()[idx];
        auto first = chain.get_list();
        if (first)
        {
            return ConstHashIterator<K, V, HashFunc>(
                array, idx, first, mod_count, capacity);
        }
        ++idx;
    }
    return end();
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
ConstHashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::end() const noexcept {
    return ConstHashIterator<K, V, HashFunc>(
        array, capacity, std::shared_ptr<HashElem<K, V>>{}, mod_count, capacity);
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
ConstHashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::cbegin() const noexcept {
    size_t idx = 0;
    while (idx < capacity)
    {
        auto &chain = array.get()[idx];
        auto first = chain.get_list();
        if (first)
        {
            return ConstHashIterator<K, V, HashFunc>(
                array, idx, first, mod_count, capacity);
        }
        ++idx;
    }
    return end();
}


template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
ConstHashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::cend() const noexcept {
    return ConstHashIterator<K, V, HashFunc>(
        array, capacity, std::shared_ptr<HashElem<K, V>>{}, mod_count, capacity);
}

#pragma endregion ControlFuncs

#pragma region InnerFuncs
template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::alloc_mem(int count)
{
  if (count <= 0)
  {
    throw BadCapacityError(__FILE__, typeid(*this).name(), __LINE__);
  }
  try
  {
    array.reset(new HashChain<K, V>[count], std::default_delete<HashChain<K, V>[]>());
    mod_count.reset();
    mod_count = std::make_shared<size_t>(0);
    std::cout << "Memory allocated" << std::endl;
  }
  catch (...)
  {
    throw MemoryError(__FILE__, typeid(*this).name(), __LINE__);
  }
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::rehash()
{
  HashTable<K, V, HashFunc> hash_new(capacity * 2);
  for (int i = 0; i < capacity; i++)
  {
    auto &current_chain = array.get()[i];
    auto current_elem = current_chain.get_list();
    while (current_elem)
    {
      hash_new.insert_node(current_elem->get_key(), current_elem->get_val());
      current_elem = current_elem->get_next();
    }
  }
  this->capacity = hash_new.capacity;
  this->array = std::move(hash_new.array);
}
#pragma endregion InnerFuncs
