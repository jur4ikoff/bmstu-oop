#include "HashElem.h"

#pragma region 5Rule
template <ValidKey K, ValidValue V>
HashElem<K, V>::HashElem(const K& key, const V& val): key(key), val(val) {}

template <ValidKey K, ValidValue V>
HashElem<K, V>::HashElem(const HashElem<K, V> &og_elem):
    key(og_elem.key), val(og_elem.val), next(og_elem.next), prev(og_elem.prev) {}

template <ValidKey K, ValidValue V>
HashElem<K, V>::HashElem(HashElem<K, V> &&og_elem) {
    val = std::move(og_elem.val);
    key = std::move(og_elem.key);
    set_next(og_elem.get_next());
    set_prev(og_elem.get_prev());
}

template <ValidKey K, ValidValue V>
HashElem<K, V>::HashElem(std::pair<K, V> &node) {
    key = node.first;
    val = node.second;
}

template <ValidKey K, ValidValue V>
HashElem<K, V>& HashElem<K, V>::operator =(const HashElem<K, V> &og_elem) {
    if (this != &og_elem) {
        key = og_elem.key;
        val = og_elem.val;
        next = og_elem.next;
        prev = og_elem.prev;
    }
    return *this;
}

template <ValidKey K, ValidValue V>
HashElem<K, V>& HashElem<K, V>::operator =(HashElem<K, V> &&og_elem) {
    if (this != &og_elem) {
        key = std::move(og_elem.key);
        val = std::move(og_elem.val);
        next = std::move(og_elem.next);
        prev = std::move(og_elem.prev);
    }
    return *this;
}
#pragma endregion 5Rule

#pragma region Operators
template <ValidKey K, ValidValue V>
bool HashElem<K, V>::operator ==(const HashElem<K, V> &other_elem) const noexcept {
    return key == other_elem.get_key() && val == other_elem.get_val();
}

template <ValidKey K, ValidValue V>
bool HashElem<K, V>::operator !=(const HashElem<K, V> &other_elem) const noexcept {
    return !((*this) == other_elem);
}

template <ValidKey K, ValidValue V>
bool HashElem<K, V>::operator ==(std::pair<K, V> &node) const noexcept {
    return key == node.first && val == node.second;
}
template <ValidKey K, ValidValue V>
bool HashElem<K, V>::operator !=(std::pair<K, V> &node) const noexcept {
    return !((*this) == node);
}
#pragma endregion Operators

#pragma region OtherFuncs
template <ValidKey K, ValidValue V>
K HashElem<K, V>::get_key() const noexcept {
    return key;
}

template <ValidKey K, ValidValue V>
V HashElem<K, V>::get_val() const noexcept {
    return val;
}

template <ValidKey K, ValidValue V>
void HashElem<K, V>::set_val(const V &new_val) {
    val = new_val;
}

template <ValidKey K, ValidValue V>
void HashElem<K, V>::set_val(V &&new_val) {
    val = std::move(new_val);
}

template <ValidKey K, ValidValue V>
void HashElem<K, V>::set_next(std::shared_ptr<HashElem<K, V>> next_elem) {
    next = next_elem;
}

template <ValidKey K, ValidValue V>
void HashElem<K, V>::set_prev(std::weak_ptr<HashElem<K, V>> prev_elem) {
    prev = prev_elem;
}

template <ValidKey K, ValidValue V>
std::shared_ptr<HashElem<K, V>> HashElem<K, V>::get_next() const noexcept {
    return next;
}

template <ValidKey K, ValidValue V>
std::weak_ptr<HashElem<K, V>> HashElem<K, V>::get_prev() const noexcept {
    return prev;
}

template <ValidKey K, ValidValue V>
bool HashElem<K, V>::has_next() const noexcept {
    return next != nullptr;
}

template <ValidKey K, ValidValue V>
bool HashElem<K, V>::has_prev() const noexcept {
    return !prev.expired();
}

#pragma endregion OtherFuncs
