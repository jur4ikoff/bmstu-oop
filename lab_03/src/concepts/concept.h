#pragma once
#include <concepts>

// Проверяет, что Type — абстрактный класс
template <typename Type>
concept Abstract = std::is_abstract_v<Type>;

// Проверяет, что Type — неабстрактный класс
template <typename Type>
concept NotAbstract = !std::is_abstract_v<Type>;

// Derivative — проверяет, что Derived наследуется от Base и Base абстрактный
template <typename Derived, typename Base>
concept Derivative = std::is_abstract_v<Base> && std::is_base_of_v<Base, Derived>;

// Constructible — проверяет, что тип можно создать с данными аргументами
template <typename Type, typename... Args>
concept Constructible = requires(Args... args) {
    Type{args...};
};