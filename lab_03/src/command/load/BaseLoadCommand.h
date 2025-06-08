#pragma once
#include "BaseCommand.h"

class BaseLoadCommand : public BaseCommand
{
public:
    BaseLoadCommand() = default;
    virtual ~BaseLoadCommand() = 0;
    size_t GetDirectorId();
    size_t GetReaderId();

protected:
    size_t _reader_id; // id ридеров находится в load_manager.h
    size_t _director_id;
    // director 1 - list_view
    // director 2 - matrix_view
};