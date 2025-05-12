#pragma once

#include <concepts>
#include <iostream>
#include <type_traits>

// Концепт проверки на конвертабельность
template <typename From, typename To>
concept Convertiable = std::convertible_to<From, To>;

template <typename From, typename To>
concept Assignable = requires(From from, To to) { to = from; };

template <typename T, typename U>
concept Divisable = requires(T t, U u) { t / u; };

template <typename T, typename U>
concept Multipy = requires(T t, U u) { t * u; };

template <typename T, typename U>
concept Summable = requires(T t, U u) { t + u; };

template <typename T, typename U>
concept Substationable = requires(T t, U u) { t - u; };

template <typename T>
concept Container = requires(T t) {
    typename T::value_type;
    typename T::size_type;
    typename T::iterator;
    typename T::const_iterator;
    typename T::reverse_iterator;
    typename T::const_reverse_iterator;

    { t.size() } noexcept -> std::same_as<typename T::size_type>;

    { t.begin() } noexcept -> std::same_as<typename T::iterator>;
    { t.end() } noexcept -> std::same_as<typename T::iterator>;

    { t.cbegin() } noexcept -> std::same_as<typename T::const_iterator>;
    { t.cend() } noexcept -> std::same_as<typename T::const_iterator>;

    { t.rbegin() } noexcept -> std::same_as<typename T::reverse_iterator>;
    { t.rend() } noexcept -> std::same_as<typename T::reverse_iterator>;

    { t.crbegin() } noexcept -> std::same_as<typename T::const_reverse_iterator>;
    { t.crend() } noexcept -> std::same_as<typename T::const_reverse_iterator>;
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
concept ConvertAssignableSum = Convertiable<U, T> &&
                               Assignable<U, T> &&
                               Summable<U, T>;

template <typename T, typename U>
concept ConvertAssignableSub = Convertiable<U, T> &&
                               Assignable<U, T> &&
                               Substationable<U, T>;

template <typename T, typename U>
concept ConvertAssignableDiv = Convertiable<U, T> &&
                               Assignable<U, T> &&
                               Divisable<U, T>;

template <typename T, typename U>
concept ConvertAssignableMul = Convertiable<U, T> &&
                               Assignable<U, T> &&
                               Multipy<U, T>;

template <typename T, typename U>
concept ConvertAssignableOperationable = Convertiable<U, T> &&
                                         Assignable<U, T> &&
                                         Divisable<U, T> &&
                                         Multipy<U, T> &&
                                         Summable<U, T> &&
                                         Substationable<U, T>;

template <typename T, typename U>
concept ConvertibleToT = Convertiable<U, T>;

template <typename T, typename Con>
concept ValidContainer = Container<Con> &&
                         Convertiable<typename Con::value_type, T> &&
                         Assignable<typename Con::value_type, T>;

template <typename Iter>
concept ForwardIterator = requires(Iter it) {
    requires std::input_iterator<Iter>;

    { Iter() } -> std::same_as<Iter>;

    requires std::is_lvalue_reference_v<typename std::iterator_traits<Iter>::reference>;

    requires std::derived_from<
        typename std::iterator_traits<Iter>::iterator_category,
        std::forward_iterator_tag>;

    // Проверка инкремента
    { ++it } -> std::same_as<Iter &>;
    { it++ } -> std::same_as<Iter>;
};