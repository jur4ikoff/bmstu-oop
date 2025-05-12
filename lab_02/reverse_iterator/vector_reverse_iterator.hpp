#pragma once

#include <iostream>

#include "vector.h"
#include "vector_reverse_iterator.h"

// Конструктор по иттератору
template <ContainerType T>
VectorReverseIterator<T>::VectorReverseIterator(const VectorReverseIterator<T> &iter) noexcept
{
    this->size = iter.size;
    this->index = iter.index;
    this->piter = iter.piter;
}

// Конструктор по контейнеру
template <ContainerType T>
VectorReverseIterator<T>::VectorReverseIterator(const Vector<T> &vec) noexcept
{
    this->size = vec.size();
    this->index = vec.size() - 1;
    this->piter = vec.container;
}

template <ContainerType T>
T &VectorReverseIterator<T>::operator*() const
{
    this->check_iter(__LINE__);
    this->check_vector(__LINE__);
    return *(this->get_ptr_cur());
}

template <ContainerType T>
T *VectorReverseIterator<T>::operator->() const
{
    this->check_iter(__LINE__);
    this->check_vector(__LINE__);
    return (this->get_ptr_cur());
}

template <ContainerType T>
VectorReverseIterator<T> &VectorReverseIterator<T>::operator=(const VectorReverseIterator<T> &other)
{
    this->check_vector(__LINE__);

    this->size = other.size;
    this->index = other.index;
    this->piter = other.piter;

    return *this;
}

// Перегрузка +
template <ContainerType T>
VectorReverseIterator<T> VectorReverseIterator<T>::operator+(const int i) const noexcept
{
    VectorReverseIterator<T> new_iter(*this);
    new_iter.index -= i;
    return new_iter;
}

template <ContainerType T>
VectorReverseIterator<T> &VectorReverseIterator<T>::operator+=(const int i) noexcept
{
    this->index -= i;
    return *this;
}

// Перегрузка инкримента
template <ContainerType T>
VectorReverseIterator<T> &VectorReverseIterator<T>::operator++() noexcept
{
    (this->index)--;
    return *this;
}

template <ContainerType T>
VectorReverseIterator<T> VectorReverseIterator<T>::operator++(int) noexcept
{
    --(this->index);
    return *this;
}

// Перегрузка -
template <ContainerType T>
VectorReverseIterator<T> VectorReverseIterator<T>::operator-(const int i) const noexcept
{
    VectorReverseIterator<T> new_iter(*this);
    new_iter.index += i;
    return new_iter;
}

// Перегрузка -=
template <ContainerType T>
VectorReverseIterator<T> &VectorReverseIterator<T>::operator-=(const int i) noexcept
{
    this->index += i;
    return *this;
}

// Перегрузка декремента iter--
template <ContainerType T>
VectorReverseIterator<T> &VectorReverseIterator<T>::operator--() noexcept
{
    (this->index)++;
    return *this;
}

// Перегрузка декремента --iter
template <ContainerType T>
VectorReverseIterator<T> VectorReverseIterator<T>::operator--(int) noexcept
{
    ++(this->index);
    return *this;
}

template <ContainerType T>
typename BaseReverseIterator<T>::difference_type VectorReverseIterator<T>::operator-(const VectorReverseIterator<T> &other) const noexcept
{
    return other.index - this->index;
}

template <ContainerType T>
VectorReverseIterator<T>::operator bool() const noexcept
{
    return this->piter.lock() && this->index >= 0 && this->index < this->size;
}

template <ContainerType T>
VectorReverseIterator<T> operator+(typename BaseReverseIterator<T>::difference_type n, const VectorReverseIterator<T> &other) noexcept
{
    return other + n;
}

template <ContainerType T>
T &VectorReverseIterator<T>::operator[](int index) const
{
    this->check_iter(__LINE__);
    this->check_vector(__LINE__);

    VectorReverseIterator<T> iter(*this);
    iter += index;

    return *iter;
}
