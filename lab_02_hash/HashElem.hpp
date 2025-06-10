#include "HashElem.h"

#pragma region constructors
template <Key K, Value V>
HashElem<K, V>::HashElem(const K &key, const V &val) noexcept : _key(key), _val(val) {}

template <Key K, Value V>
HashElem<K, V>::HashElem(const HashElem<K, V> &other) noexcept : _key(other._key), _val(other._val), _next(other._next), _prev(other._prev)
{
}

template <Key K, Value V>
HashElem<K, V>::HashElem(HashElem<K, V> &&other) noexcept
{
    _val = std::move(other._val);
    _key = std::move(other._key);
    set_next(other.get_next());
    set_prev(other.get_prev());
}

template <Key K, Value V>
HashElem<K, V>::HashElem(std::pair<K, V> &node) noexcept
{
    _key = node.first;
    _val = node.second;
}

template <Key K, Value V>
HashElem<K, V> &HashElem<K, V>::operator=(const HashElem<K, V> &other) noexcept
{
    if (this != &other)
    {
        _key = other.key;
        _val = other.val;
        _next = other.next;
        _prev = other.prev;
    }
    return *this;
}

template <Key K, Value V>
HashElem<K, V> &HashElem<K, V>::operator=(HashElem<K, V> &&og_elem) noexcept
{
    if (this != &og_elem)
    {
        _key = std::move(og_elem.key);
        _val = std::move(og_elem.val);
        _next = std::move(og_elem.next);
        _prev = std::move(og_elem.prev);
    }
    return *this;
}
#pragma endregion constructors

#pragma region Operators
template <Key K, Value V>
bool HashElem<K, V>::operator==(const HashElem<K, V> &other) const noexcept
{
    return _key == other.get_key() && _val == other.get_val();
}

template <Key K, Value V>
bool HashElem<K, V>::operator!=(const HashElem<K, V> &other) const noexcept
{
    return !((*this) == other);
}

template <Key K, Value V>
bool HashElem<K, V>::operator==(std::pair<K, V> &node) const noexcept
{
    return _key == node.first && _val == node.second;
}

template <Key K, Value V>
bool HashElem<K, V>::operator!=(std::pair<K, V> &node) const noexcept
{
    return !((*this) == node);
}
#pragma endregion Operators

#pragma region getters_setters
template <Key K, Value V>
K HashElem<K, V>::get_key() const noexcept
{
    return _key;
}

template <Key K, Value V>
V HashElem<K, V>::get_val() const noexcept
{
    return _val;
}

template <Key K, Value V>
void HashElem<K, V>::set_val(const V &val) noexcept
{
    _val = val;
}

template <Key K, Value V>
void HashElem<K, V>::set_val(V &&val) noexcept
{
    _val = std::move(val);
}

template <Key K, Value V>
std::shared_ptr<HashElem<K, V>> HashElem<K, V>::get_next() const noexcept
{
    return _next;
}

template <Key K, Value V>
std::weak_ptr<HashElem<K, V>> HashElem<K, V>::get_prev() const noexcept
{
    return _prev;
}

template <Key K, Value V>
void HashElem<K, V>::set_next(std::shared_ptr<HashElem<K, V>> next) noexcept
{
    _next = next;
}

template <Key K, Value V>
void HashElem<K, V>::set_prev(std::weak_ptr<HashElem<K, V>> prev) noexcept
{
    _prev = prev;
}
#pragma endregion getters_setters

template <Key K, Value V>
bool HashElem<K, V>::has_next() const noexcept
{
    return _next != nullptr;
}

template <Key K, Value V>
bool HashElem<K, V>::has_prev() const noexcept
{
    return !_prev.expired();
}

template <Key K, Value V>
std::ostream &operator<<(std::ostream &os, HashElem<K, V> &elem)
{
    os << "[Value: " << elem.get_val() << " ; Key: " << elem.get_key() << "]";
    return os;
}