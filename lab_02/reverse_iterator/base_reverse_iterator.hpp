#pragma once

#include <ctime>

#include "base_reverse_iterator.h"
#include "iterator_exceptions.h"

template <ContainerType T>
BaseReverseIterator<T>::const_reference BaseReverseIterator<T>::operator*() const
{
    check_iter(__LINE__);
    check_vector(__LINE__);
    return *get_ptr_cur();
}

template <ContainerType T>
BaseReverseIterator<T>::const_pointer BaseReverseIterator<T>::operator->() const
{
    check_iter(__LINE__);
    check_vector(__LINE__);
    return get_ptr_cur();
}

template <ContainerType T>
bool BaseReverseIterator<T>::operator==(const BaseReverseIterator<T> &other) const noexcept
{
    return index == other.index;
}

template <ContainerType T>
bool BaseReverseIterator<T>::operator!=(const BaseReverseIterator<T> &other) const noexcept
{
    return index != other.index;
}

template <ContainerType T>
auto BaseReverseIterator<T>::operator<=>(const BaseReverseIterator<T> &other) const noexcept
{
    return index <=> other.index;
}

template <ContainerType T>
void BaseReverseIterator<T>::check_vector(int line) const
{
    if (piter.expired())
    {
        time_t now = time(NULL);
        throw errDeletedVector(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}

template <ContainerType T>
void BaseReverseIterator<T>::check_iter(int line) const
{
    if (index >= size || index < 0)
    {
        time_t now = time(NULL);
        throw errIndexOutOfRange(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}

template <ContainerType T>
BaseReverseIterator<T>::pointer BaseReverseIterator<T>::get_ptr_cur() const
{
    std::shared_ptr<T[]> piter_to_shared_ptr = piter.lock();
    return piter_to_shared_ptr.get() + index;
}

template <ContainerType T>
BaseReverseIterator<T>::operator bool() const noexcept
{
    return this->piter.lock() && this->index >= 0 && this->index < this->size;
}
