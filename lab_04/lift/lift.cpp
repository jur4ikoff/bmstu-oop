#include "lift.hpp"

liftSystem::liftSystem(QObject *parent)
    : QObject(parent)
{
    qDebug() << "Init";
}

void liftSystem::manage_floor_call_slot(int floor, direction_t direction)
{
    if (direction == DIR_DOWN)
    {
        qDebug() << "Call down from " << floor;
    }
    else if (direction == DIR_UP)
    {
        qDebug() << "Call up from " << floor;
    }
    emit from_floor_call_signal(floor, direction);
}

void liftSystem::manage_cabin_call_slot(int floor, cabin_id_t id)
{
    if (id == CID_FIRST)
    {
        qDebug() << "Call " << floor << "floor in 1 elevator";
    }
    else if (id == CID_SECOND)
    {
        qDebug() << "Call " << floor << "floor in 2 elevator";
    }
    emit from_cabin_call_signal(floor, id);
    // TODO
}
