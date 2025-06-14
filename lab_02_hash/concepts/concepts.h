#pragma once

#include <concepts>

template <typename K>
concept Comparable = requires(const K &key) {
    { key == key } -> std::convertible_to<bool>;
    { key != key } -> std::convertible_to<bool>;
};

template <typename T>
concept Assignable = requires(T a, T b) {
    a = b;
};

template <typename HashFunc, typename K>
concept HashFunctionWithCapacity = requires(HashFunc func, const K &key, size_t capacity) {
    { func(key, capacity) } -> std::convertible_to<std::size_t>;
};

template <typename T>
concept Valid = std::is_constructible_v<T> &&
                std::is_copy_constructible_v<T> &&
                std::is_move_constructible_v<T> &&
                std::is_destructible_v<T> &&
                Assignable<T>;

template <typename V>
concept Value = Valid<V>;

template <typename K>
concept Key = Valid<K>;
