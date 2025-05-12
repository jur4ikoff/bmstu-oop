#pragma once

#include <iostream>

#include "vector.h"
#include "vector_const_iterator.h"

// Конструктор по костантному итератору
template <ContainerType T>
VectorConstIterator<T>::VectorConstIterator(const VectorConstIterator<T> &iter) noexcept
{
    this->size = iter.size;
    this->index = iter.index;
    this->piter = iter.piter;
}

// Конструктор по обычному итератору
template <ContainerType T>
VectorConstIterator<T>::VectorConstIterator(const VectorIterator<T> &iter) noexcept
{
    this->size = iter.get_size();
    this->index = iter.get_index();
    this->piter = iter.get_piter();
}

template <ContainerType T>
VectorConstIterator<T>::VectorConstIterator(const Vector<T> &vec) noexcept
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
VectorConstIterator<T> VectorConstIterator<T>::operator+(const int i) const noexcept
{
    VectorConstIterator<T> new_iter(*this);
    new_iter.index += i;
    return new_iter;
}

template <ContainerType T>
VectorConstIterator<T> &VectorConstIterator<T>::operator+=(const int i) noexcept
{
    this->index += i;
    return *this;
}

template <ContainerType T>
VectorConstIterator<T> operator+(typename BaseIterator<T>::difference_type n, const VectorConstIterator<T> &other) noexcept
{
    return other + n;
}

template <ContainerType T>
VectorConstIterator<T> &VectorConstIterator<T>::operator++() noexcept
{
    (this->index)++;
    return *this;
}

template <ContainerType T>
VectorConstIterator<T> VectorConstIterator<T>::operator++(int) noexcept
{
    ++(this->index);
    return *this;
}

template <ContainerType T>
VectorConstIterator<T> VectorConstIterator<T>::operator-(const int n) const noexcept
{
    VectorConstIterator<T> new_iter(*this);
    new_iter.index -= n;

    return new_iter;
}

template <ContainerType T>
VectorConstIterator<T> &VectorConstIterator<T>::operator-=(const int n) noexcept
{
    this->index -= n;
    return *this;
}

// Перегрузка декремента
template <ContainerType T>
VectorConstIterator<T> &VectorConstIterator<T>::operator--() noexcept // iter--
{
    (this->index)--;
    return *this;
}

template <ContainerType T>
VectorConstIterator<T> VectorConstIterator<T>::operator--(int) noexcept // --iter
{
    --(this->index);
    return *this;
}

template <ContainerType T>
typename BaseIterator<T>::difference_type VectorConstIterator<T>::operator-(const VectorConstIterator<T> &other) const noexcept
{
    return this->index - other.index;
}

template <ContainerType T>
const T &VectorConstIterator<T>::operator[](int index) const
{
    this->check_iter(__LINE__);
    this->check_vector(__LINE__);

    VectorConstIterator<T> iter(*this);
    iter += index;

    return *iter;
}

template <ContainerType T>
VectorConstIterator<T>::operator bool() const noexcept
{
    return this->piter.lock() && this->index >= 0 && this->index < this->size;
}
