#ifndef HASHITERATOR_H
#define HASHITERATOR_H

#include <iterator>
#include <memory>
#include "BaseIterator.h"
#include "concepts.h"

template <Key K, Value V>
class HashElem;

template <Key K, Value V>
class HashChain;

template <Key K, Value V, typename HashFunc> requires HashFunctionWithCapacity<HashFunc, K>
class HashIterator: public BaseIterator
{
public:
    #pragma region STLAliases
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = HashElem<K, V>;
        using difference_type = std::ptrdiff_t;
        using pointer = HashElem<K, V> *;
        using reference = HashElem<K, V> &;
    #pragma endregion STLAliases

    #pragma region 5Rule
        HashIterator() = default;
        HashIterator(std::shared_ptr<HashChain<K, V>> table, size_t index,
                     std::shared_ptr<HashElem<K, V>> current, std::shared_ptr<size_t> mod_count_og, size_t capacity);
        HashIterator(const HashIterator<K, V, HashFunc>& og_iter);
        HashIterator(HashIterator<K, V, HashFunc> &&og_iter);
        ~HashIterator() = default;
        HashIterator<K, V, HashFunc>& operator =(const HashIterator<K, V, HashFunc>& other_iter);
    #pragma endregion 5Rule

    #pragma region Funcs
        void check_if_valid() const;
        size_t get_index() const override;
        size_t get_capacity() const override;
        size_t get_needed_mod_count() const;
    #pragma endregion Funcs

    #pragma region Operators
        reference operator*() const;
        pointer operator->() const;
        HashIterator& operator++();
        HashIterator& operator--();
        HashIterator operator++(int);
        HashIterator operator--(int);
        bool operator==(const HashIterator &other) const noexcept;
        bool operator!=(const HashIterator &other) const noexcept;
    #pragma endregion Operators
private:
    std::weak_ptr<HashChain<K, V>> table;
    std::shared_ptr<HashElem<K, V>> current;
    std::shared_ptr<size_t> mod_count_ptr;
    size_t mod_count;
    size_t index;
    size_t capacity;
    void advance_to_valid();
};

#endif // HASHITERATOR_H
