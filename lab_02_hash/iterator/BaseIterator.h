#ifndef BASEITERATOR_H
#define BASEITERATOR_H

class BaseIterator
{
public:
    virtual ~BaseIterator() = default;
    virtual size_t get_index() const = 0;
    virtual size_t get_capacity() const = 0;

    //     template <ContainerType T>
    // void BaseReverseIterator<T>::check_vector(int line) const
    // {
    //     if (piter.expired())
    //     {
    //         time_t now = time(NULL);
    //         throw errDeletedVector(__FILE__, line, typeid(*this).name(), ctime(&now));
    //     }
    // }

    // template <ContainerType T>
    // void BaseReverseIterator<T>::check_iter(int line) const
    // {
    //     if (index >= size || index < 0)
    //     {
    //         time_t now = time(NULL);
    //         throw errIndexOutOfRange(__FILE__, line, typeid(*this).name(), ctime(&now));
    //     }
    // }
protected:
    size_t index;
    size_t capacity;
};

#endif // BASEITERATOR_H
