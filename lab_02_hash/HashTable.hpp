#include "HashTable.h"
#include "hash_table_exceptions.h"

#include <iostream>
#include <ctime>

#pragma region 5Rule
template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>::HashTable()
{
  _capacity = 1;
  this->memory_allocation(_capacity);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>::HashTable(int new_capacity)
{
  this->check_capacity(new_capacity);

  _capacity = new_capacity;
  mod_count = 0;
  this->memory_allocation(_capacity);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>::HashTable(std::initializer_list<std::pair<K, V>> list_elems, int new_capacity)
{
  this->check_capacity(new_capacity);

  _capacity = new_capacity;
  mod_count = 0;
  alloc_mem(_capacity);
  for (auto one_pair : list_elems)
  {
    insert_node(one_pair);
  }
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>::HashTable(const HashTable &og_hash)
{
  _capacity = og_hash._capacity;
  alloc_mem(_capacity);
  *(mod_count) = *(og_hash.mod_count);
  for (int i = 0; i < _capacity; i++)
  {
    array.get()[i] = og_hash.array.get()[i];
  }
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc>::HashTable(HashTable &&og_hash)
{
  _capacity = og_hash._capacity;
  mod_count = std::move(og_hash.mod_count);
  array = std::move(og_hash.array);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc> HashTable<K, V, HashFunc>::operator=(const HashTable<K, V, HashFunc> &other_table)
{
  if (this == &other_table)
    return *this;
  _capacity = other_table._capacity;
  alloc_mem(_capacity);
  *(mod_count) = *(other_table.mod_count);
  for (int i = 0; i < _capacity; i++)
  {
    array.get()[i] = other_table.array.get()[i];
  }
  (*mod_count)++;
  return (*this);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
template <std::ranges::input_range R>
  requires std::convertible_to<std::ranges::range_value_t<R>, std::pair<K, V>>
HashTable<K, V, HashFunc>::HashTable(R &&range)
{
  for (const auto &elem : range)
  {
    insert_node(elem.first, elem.second);
  }
}

#pragma endregion 5Rule

#pragma region Operators
template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
V &HashTable<K, V, HashFunc>::operator[](const K &key)
{
  return get_val(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
const V &HashTable<K, V, HashFunc>::operator[](const K &key) const
{
  return get_val(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
V &HashTable<K, V, HashFunc>::operator[](K &&key)
{
  return get_val(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
const V &HashTable<K, V, HashFunc>::operator[](K &&key) const
{
  return get_val(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::operator==(const HashTable<K, V, HashFunc> &other) const noexcept
{
  if (_capacity != other._capacity || get_count() != other.get_count())
  {
    return false;
  }
  for (int i = 0; i < _capacity; i++)
  {
    if (*(array.get()[i]) != *(other.array.get()[i]))
      return false;
  }
  return true;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::operator!=(const HashTable<K, V, HashFunc> &other) const noexcept
{
  return !((*this) == other);
}

// Операторы добавления
template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc> &HashTable<K, V, HashFunc>::operator+(const std::pair<K, V> &pair)
{
  insert_node(pair.first, pair.second);
  return *this;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc> &HashTable<K, V, HashFunc>::operator+(std::pair<K, V> &&pair)
{
  insert_node(std::move(pair.first), std::move(pair.second));
  return *this;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc> &HashTable<K, V, HashFunc>::operator+(const HashElem<K, V> &elem)
{
  insert_node(elem);
  return *this;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc> &HashTable<K, V, HashFunc>::operator+(
    std::initializer_list<std::pair<K, V>> list)
{
  insert_nodes(list);
  return *this;
}

// Операторы удаления
template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc> &HashTable<K, V, HashFunc>::operator-(const K &key)
{
  delete_node(key);
  return *this;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc> &HashTable<K, V, HashFunc>::operator-(K &&key)
{
  delete_node(std::move(key));
  return *this;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc> &HashTable<K, V, HashFunc>::operator-(const HashElem<K, V> &elem)
{
  delete_node(elem);
  return *this;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashTable<K, V, HashFunc> &HashTable<K, V, HashFunc>::operator-(
    std::initializer_list<K> keys)
{
  for (const auto &key : keys)
  {
    delete_node(key);
  }
  return *this;
}
#pragma endregion Operators

#pragma region OtherFuncs
template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
double HashTable<K, V, HashFunc>::calc_load_factor() const noexcept
{
  return (double)get_count() / (double)_capacity;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::empty() const noexcept
{
  return get_count() == 0;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
size_t HashTable<K, V, HashFunc>::get_mod_count() const noexcept
{
  return *mod_count;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
size_t HashTable<K, V, HashFunc>::get_capacity() const noexcept
{
  return _capacity;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
size_t HashTable<K, V, HashFunc>::get_count() const noexcept
{
  int total_count = 0;
  for (int i = 0; i < _capacity; i++)
  {
    auto &current_chain = array.get()[i];
    total_count += current_chain.get_count();
  }
  return total_count;
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
size_t HashTable<K, V, HashFunc>::size() const noexcept
{
  return get_count();
}

#pragma endregion OtherFuncs

#pragma region ControlFuncs
template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_node(const K &key, const V &val)
{
  size_t arr_index = HashFunc{}(key, _capacity);
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

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_node(K &&key, V &&val)
{
  insert_node(key, val);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_node(const HashElem<K, V> &elem)
{
  insert_node(elem.get_key(), elem.get_val());
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_node(std::pair<K, V> &node)
{
  insert_node(node.first, node.second);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_nodes(std::initializer_list<std::pair<K, V>> list_elems)
{
  for (auto elem : list_elems)
  {
    insert_node(elem);
  }
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::insert_nodes(std::initializer_list<HashElem<K, V>> list_elems)
{
  for (auto elem : list_elems)
  {
    insert_node(elem);
  }
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::delete_node(const K &key)
{
  size_t arr_index = HashFunc{}(key, _capacity);
  (*mod_count)++;
  array.get()[arr_index].delete_node(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::delete_node(K &&key)
{
  delete_node(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::delete_node(const HashElem<K, V> &elem)
{
  delete_node(elem.get_key());
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::delete_nodes(std::initializer_list<K> keys)
{
  for (auto key : keys)
  {
    delete_node(key);
  }
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::contains(const K &key) const noexcept
{
  size_t arr_index = HashFunc(key, _capacity);
  return array.get()[arr_index].contains(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::contains(const K &&key) const noexcept
{
  return contains(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::contains(const HashElem<K, V> &elem) const noexcept
{
  return contains(elem.get_key());
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
bool HashTable<K, V, HashFunc>::contains(std::pair<K, V> &node) const noexcept
{
  return contains(node.first);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashElem<K, V> &HashTable<K, V, HashFunc>::get_pair(const K &key) const
{
  for (int i = 0; i < _capacity; i++)
  {
    if (array.get()[i].contains(key))
    {
      return array.get()[i].get_pair(key);
    }
  }
  throw KeyNotFoundError(__FILE__, typeid(*this).name(), __LINE__);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashElem<K, V> &HashTable<K, V, HashFunc>::get_pair(K &&key) const
{
  return get_pair(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
V &HashTable<K, V, HashFunc>::get_val(const K &key) const noexcept
{
  size_t arr_index = HashFunc(key, _capacity);
  return array.get()[arr_index].get_val(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
V &HashTable<K, V, HashFunc>::get_val(K &&key) const noexcept
{
  return get_val(key);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashChain<K, V> &HashTable<K, V, HashFunc>::get_list(const int index) const
{
  this->check_index(index);
  return array.get()[index];
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::clear() noexcept
{
  (*mod_count)++;
  for (int i = 0; i < _capacity; i++)
  {
    array.get()[i].clear();
  }
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::begin() noexcept
{
  size_t idx = 0;
  while (idx < _capacity)
  {
    auto &chain = array.get()[idx];
    auto first = chain.get_list();
    if (first)
    {
      return HashIterator<K, V, HashFunc>(
          array, idx, first, mod_count, _capacity);
    }
    ++idx;
  }
  return end();
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::end() noexcept
{
  return HashIterator<K, V, HashFunc>(
      array, _capacity, std::shared_ptr<HashElem<K, V>>{}, mod_count, _capacity);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
ConstHashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::begin() const noexcept
{
  size_t idx = 0;
  while (idx < _capacity)
  {
    auto &chain = array.get()[idx];
    auto first = chain.get_list();
    if (first)
    {
      return ConstHashIterator<K, V, HashFunc>(
          array, idx, first, mod_count, _capacity);
    }
    ++idx;
  }
  return end();
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
ConstHashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::end() const noexcept
{
  return ConstHashIterator<K, V, HashFunc>(
      array, _capacity, std::shared_ptr<HashElem<K, V>>{}, mod_count, _capacity);
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
ConstHashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::cbegin() const noexcept
{
  size_t idx = 0;
  while (idx < _capacity)
  {
    auto &chain = array.get()[idx];
    auto first = chain.get_list();
    if (first)
    {
      return ConstHashIterator<K, V, HashFunc>(
          array, idx, first, mod_count, _capacity);
    }
    ++idx;
  }
  return end();
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
ConstHashIterator<K, V, HashFunc> HashTable<K, V, HashFunc>::cend() const noexcept
{
  return ConstHashIterator<K, V, HashFunc>(
      array, _capacity, std::shared_ptr<HashElem<K, V>>{}, mod_count, _capacity);
}

#pragma endregion ControlFuncs

#pragma region inner_functions
template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::memory_allocation(int count)
{
  this->check_capacity(count);
  try
  {
    array.reset(new HashChain<K, V>[count], std::default_delete<HashChain<K, V>[]>());
    mod_count.reset();
    mod_count = std::make_shared<size_t>(0);
    std::cout << "Memory allocated" << std::endl;
  }
  catch (...)
  {
    time_t now = time(NULL);
    throw MemoryError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
  }
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::rehash()
{
  HashTable<K, V, HashFunc> hash_new(_capacity * 2);
  for (int i = 0; i < _capacity; i++)
  {
    auto &current_chain = array.get()[i];
    auto current_elem = current_chain.get_list();
    while (current_elem)
    {
      hash_new.insert_node(current_elem->get_key(), current_elem->get_val());
      current_elem = current_elem->get_next();
    }
  }
  this->_capacity = hash_new._capacity;
  this->array = std::move(hash_new.array);
}
#pragma endregion inner_functions

#pragma region private_functions

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::check_capacity(const HashTable::size_type capacity) const
{
  if (capacity <= 0)
  {
    time_t now = time(NULL);
    throw BadCapacityError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
  }
}

template <Key K, Value V, typename HashFunc>
  requires HashFunctionWithCapacity<HashFunc, K>
void HashTable<K, V, HashFunc>::check_index(const int index) const
{
  if (index >= _capacity || index < 0)
  {
    throw TableIndexOutOfRange(__FILE__, typeid(*this).name(), __LINE__);
  }
}
#pragma endregion private_functions