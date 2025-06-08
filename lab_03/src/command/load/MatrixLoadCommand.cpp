#include "MatrixLoadCommand.h"

MatrixLoadCommand::MatrixLoadCommand()
{
    _director_id = MATRIX_BONE_MODEL_DIRECTOR_CREATOR_ID;
}

void MatrixLoadCommand::Execute()
{
}

std::string MatrixLoadCommand::GetDescription() const
{
    return "Загрузка модели с матричным представлением";
}