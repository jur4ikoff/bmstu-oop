#include "hash_chain.h"
#include "hash_node.h"
#include "hash_table_exceptions.h"

#pragma region 5Rule

template <Key K, Value V>
HashChain<K, V>::HashChain()
{
  count = 0;
  list = nullptr;
}

template <Key K, Value V>
HashChain<K, V>::HashChain(const HashChain<K, V> &og_chain)
{
  count = 0;
  if (og_chain.count != 0)
  {
    auto src_current = og_chain.list;
    list = std::make_shared<HashNode<K, V>>(src_current->get_key(), src_current->get_val());
    auto dst_current = list;
    count = 1;
    src_current = src_current->get_next();
    while (src_current)
    {
      auto new_elem = std::make_shared<HashNode<K, V>>(src_current->get_key(), src_current->get_val());
      new_elem->set_prev(dst_current);
      dst_current->set_next(new_elem);
      dst_current = new_elem;
      src_current = src_current->get_next();
      count++;
    }
  }
}

template <Key K, Value V>
HashChain<K, V>::HashChain(HashChain<K, V> &&og_chain) : count(og_chain.count)
{
  list = std::move(og_chain.list);
}

template <Key K, Value V>
HashChain<K, V>::HashChain(std::initializer_list<std::pair<K, V>> list_elems)
{
  count = 0;
  for (auto one_pair : list_elems)
  {
    if (!contains(one_pair.first))
      count++;
    insert_node(one_pair);
  }
}

template <Key K, Value V>
HashChain<K, V> &HashChain<K, V>::operator=(const HashChain<K, V> &og_chain)
{
  if (this == &og_chain)
  {
    return *this;
  }
  list.reset();
  count = 0;
  if (og_chain.count == 0)
  {
    return *this;
  }
  auto src_current = og_chain.list;
  list = std::make_shared<HashNode<K, V>>(src_current->get_key(), src_current->get_val());
  auto dst_current = list;
  count = 1;
  src_current = src_current->get_next();
  while (src_current)
  {
    auto new_elem = std::make_shared<HashNode<K, V>>(src_current->get_key(), src_current->get_val());
    new_elem->set_prev(dst_current);
    dst_current->set_next(new_elem);
    dst_current = new_elem;
    src_current = src_current->get_next();
    count++;
  }
  return *this;
}

template <Key K, Value V>
HashChain<K, V> &HashChain<K, V>::operator=(std::initializer_list<std::pair<K, V>> list_elems)
{
  list.reset();
  count = 0;
  for (auto one_pair : list_elems)
  {
    if (!contains(one_pair.first))
      count++;
    insert_node(one_pair);
  }
  return *this;
}
#pragma endregion 5Rule

#pragma region Operators
template <Key K, Value V>
bool HashChain<K, V>::operator==(const HashChain<K, V> &other_chain) const
{
  if (count != other_chain.count)
    return false;
  std::shared_ptr<HashNode<K, V>> current = list;
  std::shared_ptr<HashNode<K, V>> current_other = other_chain.list;
  while (current)
  {
    if (current->get_key() != current_other->get_key() || current->get_val() != current_other->get_val())
    {
      return false;
    }
    if (!current->has_next())
      break;
    current = current->get_next();
    current_other = current_other->get_next();
  }
  return true;
}

template <Key K, Value V>
bool HashChain<K, V>::operator!=(const HashChain<K, V> &other_chain) const
{
  return !((*this) == other_chain);
}

template <Key K, Value V>
bool HashChain<K, V>::operator==(std::initializer_list<std::pair<K, V>> list_elems) const
{
  HashChain<K, V> comp_chain(list_elems);
  return (*this) == comp_chain;
}

template <Key K, Value V>
bool HashChain<K, V>::operator!=(std::initializer_list<std::pair<K, V>> list_elems) const
{
  return !((*this) == list_elems);
}
#pragma endregion Operators

#pragma region OtherFuncs
template <Key K, Value V>
bool HashChain<K, V>::contains(const K &key)
{
  auto current = list;
  while (current)
  {
    if (current->get_key() == key)
    {
      return true;
    }
    if (!current->has_next())
      break;
    current = current->get_next();
  }
  return false;
}

template <Key K, Value V>
bool HashChain<K, V>::contains(K &&key)
{
  return contains(key);
}

template <Key K, Value V>
void HashChain<K, V>::insert_node(const K &key, const V &val)
{
  if (!list)
  {
    auto new_elem = std::make_shared<HashNode<K, V>>(key, val);
    list = new_elem;
    count++;
    return;
  }
  auto current = list;
  while (current)
  {
    if (current->get_key() == key)
    {
      current->set_val(val);
      return;
    }
    if (!current->has_next())
      break;
    current = current->get_next();
  }
  auto new_elem = std::make_shared<HashNode<K, V>>(key, val);
  new_elem->set_prev(current);
  current->set_next(new_elem);
  count++;
}

template <Key K, Value V>
void HashChain<K, V>::insert_node(K &&key, V &&val)
{
  insert_node(key, val);
}

template <Key K, Value V>
void HashChain<K, V>::insert_node(std::pair<K, V> &node)
{
  insert_node(node.first, node.second);
}

template <Key K, Value V>
void HashChain<K, V>::delete_node(const K &key)
{
  if (count == 0)
    return;
  auto current = list;
  while (current)
  {
    if (current->get_key() == key)
    {
      auto next = current->get_next();
      auto prev = current->get_prev().lock();
      if (next)
      {
        next->set_prev(current->get_prev());
      }
      if (prev)
      {
        prev->set_next(current->get_next());
      }
      if (current == list)
      {
        list = next;
      }
      count--;
      return;
    }
    current = current->get_next();
  }
  throw KeyNotFoundError(__FILE__, typeid(*this).name(), __LINE__);
}

template <Key K, Value V>
void HashChain<K, V>::delete_node(K &&key)
{
  delete_node(key);
}

template <Key K, Value V>
HashNode<K, V> &HashChain<K, V>::get_pair(const K &key) const
{
  auto current = list;
  while (current)
  {
    if (current->get_key() == key)
    {
      return *current;
    }
    current = current->get_next();
  }
  throw KeyNotFoundError(__FILE__, typeid(*this).name(), __LINE__);
}

template <Key K, Value V>
HashNode<K, V> &HashChain<K, V>::get_pair(K &&key) const
{
  return get_pair(key);
}

template <Key K, Value V>
V &HashChain<K, V>::get_val(const K &key)
{
  auto current = list;
  while (current)
  {
    if (current->get_key() == key)
      return current->get_val();
    current = current->get_next();
  }
  throw KeyNotFoundError(__FILE__, typeid(*this).name(), __LINE__);
}

template <Key K, Value V>
V &HashChain<K, V>::get_val(K &&key)
{
  get_val(key);
}

template <Key K, Value V>
int HashChain<K, V>::get_count()
{
  return count;
}

template <Key K, Value V>
std::shared_ptr<HashNode<K, V>> HashChain<K, V>::get_list()
{
  return list;
}

template <Key K, Value V>
void HashChain<K, V>::clear() noexcept
{
  list.reset();
  count = 0;
}

#pragma endregion OtherFuncs
