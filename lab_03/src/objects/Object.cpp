#include "Object.h"
#include "Visitor.h"

std::size_t GetNextId()
{
    static std::size_t id = 0;
    return ++id;
}

Object::Object() : _id(GetNextId()) {}

Object::~Object() {}
