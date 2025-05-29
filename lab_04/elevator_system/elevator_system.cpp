#include "elevator_system.hpp"

ElevatorSystem::ElevatorSystem(QObject *parent)
    : QObject(parent), _state(ELSYS_FREE)
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

void ElevatorSystem::manage_cabin_call_slot(int floor, cabin_id_t cabin_id)
{
    _state = ELSYS_CABIN_CALL;
    if (cabin_id == CID_FIRST)
    {
        qDebug() << "Call " << floor << "floor in 1 elevator";
    }
    else if (cabin_id == CID_SECOND)
    {
        qDebug() << "Call " << floor << "floor in 2 elevator";
    }
}
