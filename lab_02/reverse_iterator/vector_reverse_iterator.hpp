#pragma once

#include <iostream>

#include "vector.h"
#include "vector_reverse_iterator.h"

// Конструктор по иттератору
// template <ContainerType T>
// VectorIterator<T>::VectorIterator(const VectorIterator<T> &iter)
// {
//     this->size = iter.size;
//     this->index = iter.index;
//     this->piter = iter.piter;
// }

// // Конструктор по контейнеру
// template <ContainerType T>
// VectorIterator<T>::VectorIterator(const Vector<T> &vec)
// {
//     this->size = vec.size();
//     this->index = 0;
//     this->piter = vec.container;
// }

// template <ContainerType T>
// T &VectorIterator<T>::operator*() const
// {
//     this->check_iter(__LINE__);
//     this->check_vector(__LINE__);
//     return *(this->get_ptr_cur());
// }

// template <ContainerType T>
// T *VectorIterator<T>::operator->() const
// {
//     this->check_iter(__LINE__);
//     this->check_vector(__LINE__);
//     return (this->get_ptr_cur());
// }

// template <ContainerType T>
// VectorIterator<T> &VectorIterator<T>::operator=(const VectorIterator<T> &other)
// {
//     this->check_vector(__LINE__);

//     this->size = other.size;
//     this->index = other.index;
//     this->piter = other.piter;

//     return *this;
// }

// // Перегрузка +
// template <ContainerType T>
// VectorIterator<T> VectorIterator<T>::operator+(const int i) const
// {
//     this->check_vector(__LINE__);
//     VectorIterator<T> new_iter(*this);
//     new_iter.index += i;
//     return new_iter;
// }

// template <ContainerType T>
// VectorIterator<T> &VectorIterator<T>::operator+=(const int i)
// {
//     this->check_vector(__LINE__);
//     this->index += i;
//     return *this;
// }

// // Перегрузка инкримента
// template <ContainerType T>
// VectorIterator<T> &VectorIterator<T>::operator++()
// {
//     this->check_iter(__LINE__);
//     this->check_vector(__LINE__);
//     (this->index)++;
//     return *this;
// }

// template <ContainerType T>
// VectorIterator<T> VectorIterator<T>::operator++(int)
// {
//     this->check_iter(__LINE__);
//     this->check_vector(__LINE__);
//     ++(this->index);
//     return *this;
// }

// // Перегрузка -
// template <ContainerType T>
// VectorIterator<T> VectorIterator<T>::operator-(const int i) const
// {
//     this->check_vector(__LINE__);
//     VectorIterator<T> new_iter(*this);
//     new_iter.index -= i;
//     return new_iter;
// }

// // Перегрузка -=
// template <ContainerType T>
// VectorIterator<T> &VectorIterator<T>::operator-=(const int i)
// {
//     this->check_vector(__LINE__);
//     this->index -= i;
//     return *this;
// }

// // Перегрузка декремента iter--
// template <ContainerType T>
// VectorIterator<T> &VectorIterator<T>::operator--()
// {
//     this->check_iter(__LINE__);
//     this->check_vector(__LINE__);
//     (this->index)--;
//     return *this;
// }

// // Перегрузка декремента --iter
// template <ContainerType T>
// VectorIterator<T> VectorIterator<T>::operator--(int)
// {
//     this->check_iter(__LINE__);
//     this->check_vector(__LINE__);
//     --(this->index);
//     return *this;
// }

// template <ContainerType T>
// typename BaseIterator<T>::difference_type VectorIterator<T>::operator-(const VectorIterator<T> &other) const
// {
//     this->check_iter(__LINE__);
//     other.check_iter(__LINE__);

//     return this->index - other.index;
// }

// template <ContainerType T>
// VectorIterator<T>::operator bool() const
// {
//     return this->piter.lock() != nullptr && this->index >= 0 && this->index < this->size;
// }

// template <ContainerType T>
// VectorIterator<T> operator+(typename BaseIterator<T>::difference_type n, const VectorIterator<T> &other)
// {
//     other.check_iter(__LINE__);
//     other.check_vector(__LINE__);

//     return other + n;
// }

// template <ContainerType T>
// T &VectorIterator<T>::operator[](int dist) const
// {
//     this->check_iter(__LINE__);
//     this->check_vector(__LINE__);

//     VectorIterator<T> tmp(*this);
//     for (int i = 0; i < dist; ++i)
//     {
//         ++tmp;
//     }

//     return *tmp;
// }
