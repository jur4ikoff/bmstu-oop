#ifndef HASHELEM_H
#define HASHELEM_H

#include <memory>
#include "Concepts.h"

template <ValidKey K, ValidValue V>
class HashChain;

template <ValidKey K, ValidValue V>
class HashElem
{
    friend HashChain<K, V>;
public:
    #pragma region 5Rule
        HashElem(const K& key, const V& val);
        explicit HashElem(const HashElem<K, V> &og_elem);
        HashElem(HashElem<K, V> &&og_elem);
        HashElem(std::pair<K, V> &node);
        ~HashElem() = default;
        HashElem<K, V>& operator =(const HashElem<K, V> &og_elem);
        HashElem<K, V>& operator =(HashElem<K, V> &&og_elem);
    #pragma endregion 5Rule

    #pragma region Operators
        bool operator ==(const HashElem<K, V> &other_elem) const noexcept;
        bool operator !=(const HashElem<K, V> &other_elem) const noexcept;
        bool operator ==(std::pair<K, V> &node) const noexcept;
        bool operator !=(std::pair<K, V> &node) const noexcept;
    #pragma endregion Operators

    #pragma region Other
        K get_key() const noexcept;
        V get_val() const noexcept;
        void set_val(const V &new_val);
        void set_val(V &&new_val);
        std::shared_ptr<HashElem<K, V>> get_next() const noexcept;
        std::weak_ptr<HashElem<K, V>> get_prev() const noexcept;
        bool has_next() const noexcept;
        bool has_prev() const noexcept;
    #pragma endregion Other
private:
    K key;
    V val;
    std::shared_ptr<HashElem<K, V>> next;
    std::weak_ptr<HashElem<K, V>> prev;
    void set_next(std::shared_ptr<HashElem<K, V>> next_elem);
    void set_prev(std::weak_ptr<HashElem<K, V>> prev_elem);
};

// вывод через std::cout;
template<ValidKey K, ValidValue V>
std::ostream& operator <<(std::ostream& os, HashElem<K, V>& elem)
{
    os << "[Value: " << elem.get_val() << " ; Key: " << elem.get_key() << "]";
    return os;
}

#endif // HASHELEM_H
