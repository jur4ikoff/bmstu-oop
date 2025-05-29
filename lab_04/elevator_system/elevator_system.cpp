#include "elevator_system.hpp"

ElevatorSystem::ElevatorSystem(QObject *parent) : QObject(parent), _state(ELSYS_FREE)
{
    qDebug() << "Init";
}

void ElevatorSystem::manage_floor_call_slot(int floor, direction_t direction)
{
    _state = ELSYS_CABIN_CALL;
    if (direction == DIR_DOWN)
    {
        qDebug() << "Call down from " << floor;
    }
    else if (direction == DIR_UP)
    {
        qDebug() << "Call up from " << floor;
    }
    // TO DO
}
