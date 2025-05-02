#pragma once

#include <ctime>

#include "base_iterator.h"
#include "vector_exceptions.h"

template <ContainerType T>
const T &BaseIterator<T>::operator*() const
{
    check_iter(__LINE__);
    check_vector(__LINE__);
    return *get_ptr_cur();
}

template <ContainerType T>
const T *BaseIterator<T>::operator->() const
{
    check_iter(__LINE__);
    check_vector(__LINE__);
    return get_ptr_cur();
}

template <ContainerType T>
bool BaseIterator<T>::operator==(const BaseIterator<T> &other) const
{
    check_vector(__LINE__);
    return index == other.index;
}

template <ContainerType T>
bool BaseIterator<T>::operator!=(const BaseIterator<T> &other) const
{
    check_vector(__LINE__);
    return index != other.index;
}

// Вспомогательные функции

template <ContainerType T>
void BaseIterator<T>::check_vector(int line) const
{
    if (piter.expired())
    {
        time_t now = time(NULL);
        throw errDeletedVector(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}

template <ContainerType T>
void BaseIterator<T>::check_iter(int line) const
{
    if (index >= my_size)
    {
        time_t now = time(NULL);
        throw errIndexOutOfRange(__FILE__, line, typeid(*this).name(), ctime(&now));
    }
}

template <ContainerType T>
T *BaseIterator<T>::get_ptr_cur() const
{
    std::shared_ptr<T[]> piter_to_shared_ptr = piter.lock();
    return piter_to_shared_ptr.get() + index;
}
