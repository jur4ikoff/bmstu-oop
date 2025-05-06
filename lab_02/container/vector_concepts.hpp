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

    { t.container_size() } noexcept -> std::same_as<typename T::size_type>;

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

// template <typename T>
// concept Iterator = requires(T t) {
//     typename T::value_type;
//     typename T::pointer;
//     typename T::reference;
//     typename T::difference_type;
// };

// template <typename T>
// concept Comparable = requires(T a, T b) {
//     { a == b } -> std::same_as<bool>;
//     { a != b } -> std::same_as<bool>;
// };

// template <typename T>
// concept Incrementable = requires(T a) {
//     { a++ } -> std::same_as<T>;
//     { ++a } -> std::same_as<T>;
// };

// template <typename T, typename U>
// concept TypeDerivedFrom = std::is_base_of<T, U>::value;

// template <typename T>
// concept InputIterator = Iterator<T> &&
//                         requires { typename T::iterator_category; } &&
//                         Comparable<T> &&
//                         TypeDerivedFrom<typename T::iterator_category, std::input_iterator_tag>;

// template <typename T>
// concept ForwardIterator = InputIterator<T> &&
//                           Incrementable<T> &&
//                           TypeDerivedFrom<typename T::iterator_category, std::forward_iterator_tag>;

// template <typename Iter>
// concept ForwardIterator = std::forward_iterator<Iter>;

template <typename Iter>
concept ForwardIterator = requires(Iter it) {
    // Должен удовлетворять требованиям input iterator
    requires std::input_iterator<Iter>;

    // Должен быть default-конструируемым
    { Iter() } -> std::same_as<Iter>;

    // Должен поддерживать multi-pass (сохраняемое состояние)
    requires std::is_lvalue_reference_v<typename std::iterator_traits<Iter>::reference>;

    // Должен иметь правильный category tag
    requires std::derived_from<
        typename std::iterator_traits<Iter>::iterator_category,
        std::forward_iterator_tag>;

    // Проверка инкремента
    { ++it } -> std::same_as<Iter &>;
    { it++ } -> std::same_as<Iter>;
};