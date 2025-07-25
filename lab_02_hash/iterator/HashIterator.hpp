#include "HashIterator.h"
#include "iterator_exceptions.h"

#pragma region 5Rule

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc>::HashIterator(
    std::shared_ptr<HashChain<K, V>> table,
    size_t index,
    std::shared_ptr<HashNode<K, V>> current,
    size_t capacity)
    : table(table), index(index), current(current),
      capacity(capacity)
{
    if (!current)
        advance_to_valid();
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc>::HashIterator(const HashIterator &og_iter)
    : table(og_iter.table), index(og_iter.index),
      current(og_iter.current), capacity(og_iter.capacity)
{
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc>::HashIterator(HashIterator &&og_iter)
    : table(std::move(og_iter.table)), index(og_iter.index),
      current(std::move(og_iter.current)), capacity(og_iter.capacity)
{
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> &HashIterator<K, V, HashFunc>::operator=(const HashIterator &other_iter)
{
    if (this != &other_iter)
    {
        table = other_iter.table;
        index = other_iter.index;
        current = other_iter.current;
        capacity = other_iter.capacity;
    }
    return *this;
}

#pragma endregion

#pragma region Funcs

// template <Key K, Value V, typename HashFunc>
//     requires HashFunctionWithCapacity<HashFunc, K>
// void HashIterator<K, V, HashFunc>::check_iter() const
// {
//     // Проверка, что он существует вообще
//     if (index >= capacity)
//     {
//         time_t now = time(NULL);
//         throw IteratorTableWasChanged(__FILE__, typeid(*this).name(), __LINE__);
//     }
//     // if (mod_count_ptr && mod_count != *mod_count_ptr)
//     //     throw IteratorTableWasChanged(__FILE__, typeid(*this).name(), __LINE__);
// }

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
void HashIterator<K, V, HashFunc>::check_if_valid() const
{
    if (index >= capacity)
    {
        time_t now = time(NULL);
        throw IteratorIndexOutOfRange(__FILE__, typeid(*this).name(), __LINE__, ctime(&now));
    }
    // if (mod_count_ptr && mod_count != *mod_count_ptr)
    //     throw IteratorTableWasChanged(__FILE__, typeid(*this).name(), __LINE__);
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
size_t HashIterator<K, V, HashFunc>::get_index() const
{
    return index;
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
size_t HashIterator<K, V, HashFunc>::get_capacity() const
{
    return capacity;
}

// template <Key K, Value V, typename HashFunc>
//     requires HashFunctionWithCapacity<HashFunc, K>
// size_t HashIterator<K, V, HashFunc>::get_needed_mod_count() const
// {
//     return mod_count;
// }

#pragma endregion

#pragma region Operators

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
typename HashIterator<K, V, HashFunc>::reference
HashIterator<K, V, HashFunc>::operator*() const
{
    check_if_valid();
    return *current;
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
typename HashIterator<K, V, HashFunc>::pointer
HashIterator<K, V, HashFunc>::operator->() const
{
    check_if_valid();
    return current.get();
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> &HashIterator<K, V, HashFunc>::operator++()
{
    if (current && current->has_next())
    {
        current = current->get_next();
    }
    else
    {
        ++index;
        current = nullptr;
        advance_to_valid();
    }
    return *this;
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> &HashIterator<K, V, HashFunc>::operator--()
{
    check_if_valid();
    auto chains = table.lock();
    if (!chains)
        throw IteratorDoesntExistError(__FILE__, typeid(*this).name(), __LINE__);

    if (!current)
    {
        index = capacity;
        while (index > 0)
        {
            --index;
            auto elem = chains.get()[index].get_list();
            if (elem)
            {
                while (elem->has_next())
                    elem = elem->get_next();
                current = elem;
                return *this;
            }
        }
        return *this;
    }

    if (current->has_prev())
    {
        current = current->get_prev().lock();
    }
    else
    {
        while (index > 0)
        {
            --index;
            auto elem = chains.get()[index].get_list();
            if (elem)
            {
                while (elem->has_next())
                    elem = elem->get_next();
                current = elem;
                return *this;
            }
        }
        current = nullptr;
    }
    return *this;
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> HashIterator<K, V, HashFunc>::operator++(int)
{
    HashIterator tmp = *this;
    ++(*this);
    return tmp;
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> HashIterator<K, V, HashFunc>::operator--(int)
{
    HashIterator tmp = *this;
    --(*this);
    return tmp;
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
bool HashIterator<K, V, HashFunc>::operator==(const HashIterator &other) const noexcept
{
    return current == other.current && index == other.index;
}

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
bool HashIterator<K, V, HashFunc>::operator!=(const HashIterator &other) const noexcept
{
    return !(*this == other);
}

#pragma endregion

#pragma region advance_to_valid

template <Key K, Value V, typename HashFunc>
    requires HashFunctionWithCapacity<HashFunc, K>
void HashIterator<K, V, HashFunc>::advance_to_valid()
{
    auto chains = table.lock();
    if (!chains)
        return;

    while (!current && index < capacity)
    {
        current = chains.get()[index].get_list();
        if (!current)
            ++index;
    }
}

#pragma endregion
