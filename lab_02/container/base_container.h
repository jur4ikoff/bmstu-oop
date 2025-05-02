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
    size_t size() const noexcept;
    virtual ~baseContainer() = 0;

protected:
    size_t len = 0;
};

#include "base_container.hpp"
