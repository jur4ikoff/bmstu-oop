#pragma once

#include <iostream>

class baseContainer
{
public:
    [[nodiscard]] bool is_empty() const noexcept;
    int size() const noexcept;
    virtual ~baseContainer() = 0;

protected:
    int container_size = 0;
};
