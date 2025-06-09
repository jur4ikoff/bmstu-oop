#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>

template <typename K>
concept Comparable = requires(const K& key) {
    { key == key } -> std::convertible_to<bool>;
    { key != key } -> std::convertible_to<bool>;
};

template <typename T>
concept Assignable = requires(T a, T b) {
    a = b;
};

template <typename HashFunc, typename K>
concept HashFunctionWithCapacity = requires(HashFunc func, const K& key, size_t capacity) {
    { func(key, capacity) } -> std::convertible_to<std::size_t>;
};

template <typename V>
concept ValidValue = std::is_constructible_v<V> &&
                     std::is_copy_constructible_v<V> &&
                     std::is_move_constructible_v<V> &&
                     std::is_destructible_v<V> &&
                     Assignable<V>;

template <typename K>
concept ValidKey = std::is_constructible_v<K> &&
                     std::is_copy_constructible_v<K> &&
                     std::is_move_constructible_v<K> &&
                     std::is_destructible_v<K> &&
                     Assignable<K> && Comparable<K>;

#endif // CONCEPTS_H
