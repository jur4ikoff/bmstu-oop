#pragma once

#include <iostream>

#include "vector.h"
#include "vector_const_iterator.h"

// Конструктор по костантному итератору
template <ContainerType T>
VectorConstIterator<T>::VectorConstIterator(const VectorConstIterator<T> &iter)
{
    this->size = iter.size;
    this->index = iter.index;
    this->piter = iter.piter;
}

// Конструктор по обычному итератору
template <ContainerType T>
VectorConstIterator<T>::VectorConstIterator(const VectorIterator<T> &iter)
{
    this->size = iter.size;
    this->index = iter.index;
    this->piter = iter.piter;
}

template <ContainerType T>
VectorConstIterator<T>::VectorConstIterator(const Vector<T> &vec)
{
    this->size = vec.size();
    this->index = 0;
    this->piter = vec.container;
}

template <ContainerType T>
VectorConstIterator<T> &VectorConstIterator<T>::operator=(const VectorConstIterator<T> &other)
{
    this->check_vector(__LINE__);
    this->size = other.size;
    this->index = other.index;
    this->piter = other.piter;
    return *this;
}


template <ContainerType T>
VectorConstIterator<T> VectorConstIterator<T>::operator+(const int i) const
{
    this->check_vector(__LINE__);
    VectorConstIterator<T>  new_iter(*this);
    new_iter.index += i;
    return new_iter;
}

template <ContainerType T>
VectorConstIterator<T> &VectorConstIterator<T>::operator += (const int i)
{
    this->check_vector(__LINE__);
    this->index += i;
    return *this;
}

template <ContainerType T>
VectorConstIterator<T> &VectorConstIterator<T>::operator ++()
{
    this->check_iter(__LINE__);
    this->check_vector(__LINE__);

    (this->index)++;
    return *this;
}

template <ContainerType T>
VectorConstIterator<T> VectorConstIterator<T>::operator ++ (int)
{
    this->check_iter(__LINE__);
    this->check_vector(__LINE__);

    ++(this->index);
    return *this;
}