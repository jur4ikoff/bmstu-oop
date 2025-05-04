#pragma once

#include "base_container.h"

baseContainer::~baseContainer() {};

bool baseContainer::is_empty() const noexcept
{
    return len == 0;
}

int baseContainer::size() const noexcept
{
    return len;
}

