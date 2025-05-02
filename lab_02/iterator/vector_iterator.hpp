#pragma once

#include <iostream>

#include "vector.h"
#include "vector_iterator.h"

// Конструктор по иттератору
template <ContainerType T>
VectorIterator<T>::VectorIterator(const VectorIterator <T> &iter)
{
    size = iter.size;
    index = iter.index;
    piter = iter.piter;
}

// Конструктор по контейнеру
template <ContainerType T>
VectorIterator<T>::VectorIterator(const Vector &vec)
{
    size = vec.size();
    index = 0;
    piter = vec.container();
}

template <ContainerType T>
T& VectorIterator<T>::operator * ()
{
    check_iter(__LINE__);
    check_vector(__LINE__);
    return *(this->get_ptr_cur());
}

template <ContainerType T>
T* VectorIterator<T>::operator -> ()
{
    check_iter(__LINE__);
    check_vector(__LINE__);
    return (this->get_ptr_cur());
}

// Перегрузка +
template <ContainerType T>
VectorIterator<T> VectorIterator<T>::operator + (const int i) const
{
    check_vector(__LINE__);
    VectorIterator<T> new_iter(*this);
    new_iter.index += i;
    return new_iter;
}

template <ContainerType T>
VectorIterator<T> &VectorIterator<T>::operator += (const int i)
{
    check_vector(__LINE__);
    index += i;
    return *this;
}

// Перегрузка инкримента
template <ContainerType T>
VectorIterator<T> &VectorIterator<T>::operator ++ ()
{
    check_iter(__LINE__);
    check_vector(__LINE__);
    index++;
    return *this;
}

template <ContainerType T>
VectorIterator<T> VectorIterator<T>::operator ++ (int)
{
    check_iter(__LINE__);
    check_vector(__LINE__);
    ++iondex;
    return *this;
}