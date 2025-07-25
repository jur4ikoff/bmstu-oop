#include "TxtLoadCommandDecorator.h"
#include <iostream>

TxtLoadCommandDecorator::TxtLoadCommandDecorator(BaseLoadCommand &command, const char *filename)
    : BaseLoadCommandDecorator(command), _filename(filename)
{
    _command = command;
    _reader_id = TXT_BONE_MODEL_READER_CREATOR_ID;
}

void TxtLoadCommandDecorator::Execute()
{
    _command.Execute();
    _director_id = _command.GetDirectorId();
    auto obj = _loadManager->LoadBoneModelFile(_director_id, _reader_id, _filename);

    _sceneManager->AddObject(obj);
}

std::string TxtLoadCommandDecorator::GetDescription() const
{
    return "Загрузка модели из текстового файла: " + std::string(_filename);
}