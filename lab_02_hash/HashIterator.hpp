#include "HashIterator.h"
#include "Errors.h"

#pragma region 5Rule

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc>::HashIterator(
    std::shared_ptr<HashChain<K, V>> table,
    size_t index,
    std::shared_ptr<HashElem<K, V>> current,
    std::shared_ptr<size_t> mod_count_og,
    size_t capacity)
    : table(table), index(index), current(current),
    mod_count_ptr(mod_count_og), mod_count(*mod_count_og),
    capacity(capacity)
{
    if (!current)
        advance_to_valid();
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc>::HashIterator(const HashIterator &og_iter)
    : table(og_iter.table), index(og_iter.index),
    current(og_iter.current), mod_count_ptr(og_iter.mod_count_ptr),
    mod_count(og_iter.mod_count), capacity(og_iter.capacity)
{
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc>::HashIterator(HashIterator &&og_iter)
    : table(std::move(og_iter.table)), index(og_iter.index),
    current(std::move(og_iter.current)), mod_count_ptr(std::move(og_iter.mod_count_ptr)),
    mod_count(og_iter.mod_count), capacity(og_iter.capacity)
{
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> &HashIterator<K, V, HashFunc>::operator=(const HashIterator &other_iter)
{
    if (this != &other_iter)
    {
        table = other_iter.table;
        index = other_iter.index;
        current = other_iter.current;
        mod_count_ptr = other_iter.mod_count_ptr;
        mod_count = other_iter.mod_count;
        capacity = other_iter.capacity;
    }
    return *this;
}
#pragma endregion

#pragma region Funcs
template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
void HashIterator<K, V, HashFunc>::check_if_valid() const
{
    if (mod_count_ptr && mod_count != *mod_count_ptr)
        throw IteratorTableWasChanged(__FILE__, typeid(*this).name(), __LINE__);
}


template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
size_t HashIterator<K, V, HashFunc>::get_index() const {
    return index;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
size_t HashIterator<K, V, HashFunc>::get_capacity() const {
    return capacity;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
size_t HashIterator<K, V, HashFunc>::get_needed_mod_count() const {
    return mod_count;
}
#pragma endregion

#pragma region Operators
template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
typename HashIterator<K, V, HashFunc>::reference
HashIterator<K, V, HashFunc>::operator*() const
{
    check_if_valid();
    return *current;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
typename HashIterator<K, V, HashFunc>::pointer
HashIterator<K, V, HashFunc>::operator->() const
{
    check_if_valid();
    return current.get();
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> &HashIterator<K, V, HashFunc>::operator++()
{
    check_if_valid();
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

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
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

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> HashIterator<K, V, HashFunc>::operator++(int)
{
    HashIterator tmp = *this;
    ++(*this);
    return tmp;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
HashIterator<K, V, HashFunc> HashIterator<K, V, HashFunc>::operator--(int)
{
    HashIterator tmp = *this;
    --(*this);
    return tmp;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
bool HashIterator<K, V, HashFunc>::operator==(const HashIterator &other) const noexcept
{
    return current == other.current && index == other.index;
}

template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
bool HashIterator<K, V, HashFunc>::operator!=(const HashIterator &other) const noexcept
{
    return !(*this == other);
}
#pragma endregion

#pragma region advance_to_valid
template <ValidKey K, ValidValue V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
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
