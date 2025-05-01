#pragma once

#include <iostream>

class baseContainer
{
public:
    // [[nodiscard]] — атрибут, указывающий, что возвращаемое значение не должно игнорироваться (иначе компилятор выдаст предупреждение).
    // virtual - Указывает, что функция может быть переопределена в производных классах
    // const - Метод не изменяет состояние объекта
    // noexcept - метод не выбрасывает исключения
    // [[nodiscard]] virtual bool empty() const noexcept = 0;
    // virtual size_t size() noexcept = 0;
    virtual ~baseContainer() = 0;

protected:  
    size_t len = 0;
};
