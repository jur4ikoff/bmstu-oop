#pragma once

#include <iostream>

class baseContainer
{
public:

using size_type = int;
    [[nodiscard]] bool is_empty() const noexcept;
    size_type size() const noexcept;
    virtual ~baseContainer() = 0;

protected:
    int container_size = 0;
};
