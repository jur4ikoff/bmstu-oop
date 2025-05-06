#include "base_container.h"

baseContainer::~baseContainer() {};

bool baseContainer::is_empty() const noexcept
{
    return container_size == 0;
}

int baseContainer::size() const noexcept
{
    return container_size;
}
