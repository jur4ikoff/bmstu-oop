#include "hash_chain.h"
#include "hash_map_exceptions.h"
#include "hash_node.h"

#pragma region five_rule

template <Key K, Value V>
HashChain<K, V>::HashChain()
{
    _count = 0;
    this->_list = nullptr;
}

template <Key K, Value V>
HashChain<K, V>::HashChain(const HashChain<K, V> &other)
{
    other.check_size();
    _count = 0;

    auto src = other._list;
    this->_list = std::make_shared<HashNode<K, V>>(src->get_key(), src->get_val());
    auto dst = this->_list;
    this->_count = 1;
    src = src->get_next();
    while (src)
    {
        auto new_elem = std::make_shared<HashNode<K, V>>(src->get_key(), src->get_val());
        new_elem->set_prev(dst);
        dst->set_next(new_elem);
        dst = new_elem;
        src = src->get_next();
        _count++;
    }
}

template <Key K, Value V>
HashChain<K, V>::HashChain(HashChain<K, V> &&other)
    : _count(other._count)
{
    _list = std::move(other._list);
}

template <Key K, Value V>
HashChain<K, V>::HashChain(std::initializer_list<std::pair<K, V>> list_elems)
{
    _count = 0;
    for (auto el : list_elems)
    {
        if (!is_contain(el.first))
        {
            _count++;
            this->insert_node(el);
        }
    }
}

template <Key K, Value V>
HashChain<K, V> &HashChain<K, V>::operator=(const HashChain<K, V> &other)
{
    if (this == &other)
    {
        return *this;
    }

    _list.reset();
    _count = 0;
    if (other._count == 0)
    {
        return *this;
    }

    auto src = other._list;
    _list = std::make_shared<HashNode<K, V>>(src->get_key(), src->get_val());
    auto dst = _list;
    _count = 1;
    src = src->get_next();
    while (src)
    {
        auto new_elem = std::make_shared<HashNode<K, V>>(src->get_key(), src->get_val());
        new_elem->set_prev(dst);
        dst->set_next(new_elem);
        dst = new_elem;
        src = src->get_next();
        _count++;
    }
    return *this;
}

template <Key K, Value V>
HashChain<K, V> &HashChain<K, V>::operator=(std::initializer_list<std::pair<K, V>> list_elems)
{
    _list.reset();
    _count = 0;
    for (auto one_pair : list_elems)
    {
        if (!is_contain(one_pair.first))
            _count++;
        insert_node(one_pair);
    }
    return *this;
}

#pragma endregion five_rule

#pragma region operators

template <Key K, Value V>
bool HashChain<K, V>::operator==(const HashChain<K, V> &other) const noexcept
{
    if (_count != other._count)
        return false;

    std::shared_ptr<HashNode<K, V>> current = _list;
    std::shared_ptr<HashNode<K, V>> current_other = other._list;
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
bool HashChain<K, V>::operator==(std::initializer_list<std::pair<K, V>> list_elems) const noexcept
{
    HashChain<K, V> other_chain(list_elems);
    return (*this) == other_chain;
}

template <Key K, Value V>
bool HashChain<K, V>::operator!=(const HashChain<K, V> &other) const noexcept
{
    return !((*this) == other);
}

template <Key K, Value V>
bool HashChain<K, V>::operator!=(std::initializer_list<std::pair<K, V>> list_elems) const noexcept
{
    return !((*this) == list_elems);
}

#pragma endregion operators

#pragma region other

template <Key K, Value V>
bool HashChain<K, V>::is_contain(const K &key) noexcept
{
    auto current = _list;
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
bool HashChain<K, V>::is_contain(K &&key) noexcept
{
    return is_contain(key);
}

template <Key K, Value V>
void HashChain<K, V>::insert_node(const K &key, const V &val) noexcept
{
    if (!_list)
    {
        auto new_elem = std::make_shared<HashNode<K, V>>(key, val);
        _list = new_elem;
        _count++;
        return;
    }

    auto current = _list;
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
    _count++;
}

template <Key K, Value V>
void HashChain<K, V>::insert_node(K &&key, V &&val) noexcept
{
    insert_node(key, val);
}

template <Key K, Value V>
void HashChain<K, V>::insert_node(std::pair<K, V> &node) noexcept
{
    insert_node(node.first, node.second);
}

template <Key K, Value V>
void HashChain<K, V>::delete_node(const K &key)
{
    if (_count == 0)
        return;
    auto current = _list;
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
            if (current == _list)
            {
                _list = next;
            }
            _count--;
            return;
        }
        current = current->get_next();
    }
    time_t now = time(NULL);
    throw KeyNotFoundError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
}

template <Key K, Value V>
void HashChain<K, V>::delete_node(K &&key)
{
    delete_node(key);
}

template <Key K, Value V>
HashNode<K, V> &HashChain<K, V>::get_pair(const K &key) const
{
    auto current = _list;
    while (current)
    {
        if (current->get_key() == key)
        {
            return *current;
        }
        current = current->get_next();
    }

    time_t now = time(NULL);
    throw KeyNotFoundError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
}

template <Key K, Value V>
HashNode<K, V> &HashChain<K, V>::get_pair(K &&key) const
{
    return get_pair(key);
}

template <Key K, Value V>
V &HashChain<K, V>::get_val(const K &key)
{
    auto current = _list;
    while (current)
    {
        if (current->get_key() == key)
            return current->get_val();
        current = current->get_next();
    }
    time_t now = time(NULL);
    throw KeyNotFoundError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
}

template <Key K, Value V>
V &HashChain<K, V>::get_val(K &&key)
{
    get_val(key);
}

template <Key K, Value V>
int HashChain<K, V>::get_count() noexcept
{
    return _count;
}

template <Key K, Value V>
std::shared_ptr<HashNode<K, V>> HashChain<K, V>::get_list() noexcept
{
    return _list;
}

template <Key K, Value V>
void HashChain<K, V>::clear() noexcept
{
    _list.reset();
    _count = 0;
}

template <Key K, Value V>
void HashChain<K, V>::check_size()
{
    if (_count < 0)
    {
        time_t now = time(NULL);
        throw BadCountError(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
    }
}

#pragma endregion other

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
