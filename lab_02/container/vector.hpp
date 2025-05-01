#pragma once

#include "base_container.hpp"

#include "vector_concepts.hpp"

template <CopyMoveAssignableNumeric T>
class Vector : public baseContainer
{
public:
    Vector() {};

    ~Vector() {};
};
