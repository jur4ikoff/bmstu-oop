#include "MatrixLoadCommand.h"

MatrixLoadCommand::MatrixLoadCommand()
{
    _reader_id = 1;
    _director_id = MATRIX_BONE_MODEL_DIRECTOR_CREATOR_ID;
}

void MatrixLoadCommand::Execute()
{
    // _director_id = 1;
}

std::string MatrixLoadCommand::GetDescription() const
{
    return "Загрузка модели с матричным представлением";
}