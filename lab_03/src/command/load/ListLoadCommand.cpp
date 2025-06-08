#include "ListLoadCommand.h"

ListLoadCommand::ListLoadCommand()
{
    _reader_id = 1;
    _director_id = LIST_BONE_MODEL_DIRECTOR_CREATOR_ID;
}

void ListLoadCommand::Execute()
{
}

std::string ListLoadCommand::GetDescription() const
{
    return "Загрузка модели (список)";
}