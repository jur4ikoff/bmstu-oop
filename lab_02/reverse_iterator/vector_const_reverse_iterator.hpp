#pragma once

#include <iostream>

#include "vector.h"
#include "vector_reverse_iterator.h"

// Конструктор по иттератору
template <ContainerType T>
VectorConstReverseIterator<T>::VectorConstReverseIterator(const VectorConstReverseIterator<T> &iter) noexcept
{
    this->size = iter.size;
    this->index = iter.index;
    this->piter = iter.piter;
}

template <ContainerType T>
VectorConstReverseIterator<T>::VectorConstReverseIterator(const VectorReverseIterator<T> &iter) noexcept
{
    this->size = iter.size;
    this->index = iter.index;
    this->piter = iter.piter;
}

// Конструктор по контейнеру
template <ContainerType T>
VectorConstReverseIterator<T>::VectorConstReverseIterator(const Vector<T> &vec) noexcept
{
    this->size = vec.size();
    this->index = vec.size() - 1;
    this->piter = vec.container;
}

template <ContainerType T>
VectorConstReverseIterator<T> &VectorConstReverseIterator<T>::operator=(const VectorConstReverseIterator<T> &other)
{
    this->check_vector(__LINE__);
    this->size = other.size;
    this->index = other.index;
    this->piter = other.piter;

    return *this;
}

// Перегрузка +
template <ContainerType T>
VectorConstReverseIterator<T> VectorConstReverseIterator<T>::operator+(const int i) const noexcept
{
    VectorConstReverseIterator<T> new_iter(*this);
    new_iter.index -= i;
    return new_iter;
}

template <ContainerType T>
VectorConstReverseIterator<T> &VectorConstReverseIterator<T>::operator+=(const int i) noexcept
{
    this->index -= i;
    return *this;
}

// Перегрузка инкримента
template <ContainerType T>
VectorConstReverseIterator<T> &VectorConstReverseIterator<T>::operator++() noexcept
{
    (this->index)--;
    return *this;
}

template <ContainerType T>
VectorConstReverseIterator<T> VectorConstReverseIterator<T>::operator++(int) noexcept
{
    --(this->index);
    return *this;
}

// Перегрузка -
template <ContainerType T>
VectorConstReverseIterator<T> VectorConstReverseIterator<T>::operator-(const int i) const noexcept
{
    VectorConstReverseIterator<T> new_iter(*this);
    new_iter.index += i;
    return new_iter;
}

// Перегрузка -=
template <ContainerType T>
VectorConstReverseIterator<T> &VectorConstReverseIterator<T>::operator-=(const int i) noexcept
{
    this->index += i;
    return *this;
}

// Перегрузка декремента iter--
template <ContainerType T>
VectorConstReverseIterator<T> &VectorConstReverseIterator<T>::operator--() noexcept
{
    (this->index)++;
    return *this;
}

// Перегрузка декремента --iter
template <ContainerType T>
VectorConstReverseIterator<T> VectorConstReverseIterator<T>::operator--(int) noexcept
{
    ++(this->index);
    return *this;
}

template <ContainerType T>
typename BaseReverseIterator<T>::difference_type VectorConstReverseIterator<T>::operator-(const VectorConstReverseIterator<T> &other) const noexcept
{
    return other.index - this->index;
}


template <ContainerType T>
VectorConstReverseIterator<T> operator+(typename BaseReverseIterator<T>::difference_type n, const VectorConstReverseIterator<T> &other) noexcept
{
    return other + n;
}

template <ContainerType T>
BaseReverseIterator<T>::const_reference VectorConstReverseIterator<T>::operator[](int index) const
{
    this->check_iter(__LINE__);
    this->check_vector(__LINE__);

    VectorConstReverseIterator<T> iter(*this);
    iter += index;

    return *iter;
}
