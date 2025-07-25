#include "SetCameraCommand.h"

SetCameraCommand::SetCameraCommand(std::size_t id) : _id(id) {}

void SetCameraCommand::Execute()
{
    _sceneManager->SetCamera(_id);
}

std::string SetCameraCommand::GetDescription() const
{
    return "Установка камеры";
}
