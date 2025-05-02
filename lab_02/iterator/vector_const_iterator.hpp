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

// // Конструктор по обычному итератору
// template <ContainerType T>
// VectorConstIterator<T>::VectorConstIterator(const VectorIterator<T> &iter)
// {
//     size = iter.size;
//     index = iter.index;
//     piter = iter.piter;
// }

// template <ContainerType T>
// VectorConstIterator<T>::VectorConstIterator(const Vector<T> &vec)
// {
//     size = vec.size();
//     index = 0;
//     piter = vec.container();
// }
