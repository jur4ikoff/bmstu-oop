#ifndef BASEITERATOR_H
#define BASEITERATOR_H

class BaseIterator
{
public:
    virtual ~BaseIterator() = default;
    virtual size_t get_index() const = 0;
    virtual size_t get_capacity() const = 0;
protected:
    size_t index;
    size_t capacity;
};

#endif // BASEITERATOR_H
