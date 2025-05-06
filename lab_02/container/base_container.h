#pragma once

#include <iostream>

class baseContainer
{
public:
    // [[nodiscard]] — атрибут, указывающий, что возвращаемое значение не должно игнорироваться (иначе компилятор выдаст предупреждение).
    // virtual - Указывает, что функция может быть переопределена в производных классах
    // const - Метод не изменяет состояние объекта
    // noexcept - метод не выбрасывает исключения
    [[nodiscard]] bool is_empty() const noexcept;
    int size() const noexcept;
    virtual ~baseContainer() = 0;

protected:
    int container_size = 0;
};

// #include "base_container.hpp"
