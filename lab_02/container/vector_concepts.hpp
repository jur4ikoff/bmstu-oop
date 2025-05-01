#pragma once

#include <concepts>

// Концепт ограничивает используемые типы
template <typename T>
concept CopyMoveAssignableNumeric = 
    std::copy_constructible<T> &&
    std::move_constructible<T> &&
    std::assignable_from<T&, T> &&
    std::is_arithmetic_v<T>;


