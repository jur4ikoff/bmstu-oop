#pragma once
#include "BaseDrawCommand.h"
#include <QGraphicsScene>

class DrawSceneQtCommand : public BaseDrawCommand
{
public:
    DrawSceneQtCommand() = delete;
    virtual ~DrawSceneQtCommand() = default;
    DrawSceneQtCommand(QGraphicsScene *sceneQt);
    virtual void Execute() override;
    virtual std::string GetDescription() const override;

private:
    QGraphicsScene *_sceneQt;
};