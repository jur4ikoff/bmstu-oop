#pragma once

#include <concepts>

// Концепт проверки на конвертабельность
template <typename From, typename To>
concept Convertiable = std::convertible_to<From, To>;

template <typename From, typename To>
concept Assignable = requires(From from, To to) { to = from; };

// Концепт ограничивает используемые типы
template <typename T>
concept ContainerType =
    std::copy_constructible<T> &&
    std::move_constructible<T> &&
    std::assignable_from<T &, T> &&
    std::is_arithmetic_v<T>;

// Концепт, что тип данных U может быть преобразован в тип данных T
template <typename T, typename U>
concept ConvertAssignable = Convertiable<U, T> &&
                            Assignable<U, T>;
