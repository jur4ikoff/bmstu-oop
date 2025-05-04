#pragma once

#include <concepts>

// Концепт проверки на конвертабельность
template <typename From, typename To>
concept Convertiable = std::convertible_to<From, To>;

template <typename From, typename To>
concept Assignable = requires(From from, To to) { to = from; };

template <typename T>
concept Container = requires(T t) {
    typename T::value_type;
    typename T::size_type;
    typename T::iterator;
    typename T::const_iterator;

    { t.size() } noexcept -> std::same_as<typename T::size_type>;

    { t.begin() } noexcept -> std::same_as<typename T::iterator>;
    { t.end() } noexcept -> std::same_as<typename T::iterator>;

    { t.cbegin() } noexcept -> std::same_as<typename T::const_iterator>;
    { t.cend() } noexcept -> std::same_as<typename T::const_iterator>;
};

// Концепт ограничивает используемые типы
template <typename T>
concept ContainerType = std::copy_constructible<T> &&
                        std::move_constructible<T> &&
                        std::assignable_from<T &, T> &&
                        std::is_arithmetic_v<T>;

// Концепт, что тип данных U может быть преобразован в тип данных T
template <typename T, typename U>
concept ConvertAssignable = Convertiable<U, T> &&
                            Assignable<U, T>;

template <typename T, typename U>
concept ConvertibleToT = Convertiable<U, T>;

template <typename T, typename Con>
concept ValidContainer = Container<Con> &&
                         Convertiable<typename Con::value_type, T> &&
                         Assignable<typename Con::value_type, T>;
