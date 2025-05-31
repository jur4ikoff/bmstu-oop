#include "cabin.hpp"

Cabin::Cabin(cabin_id_t id, QObject *parent)
    : QObject(parent), _id(id), _state(CAB_BOARDING_FINISHED), _doors(id)
{
    _move_timer.setSingleShot(true);
    qDebug() << "Cabin INIT";
}

void Cabin::cabin_free_slot()
{
    qDebug() << "Free";
}

void Cabin::cabin_moving_slot(direction_t direction)
{
    if (direction == DIR_UP)
    {
        qDebug() << "Upper";
    }
    else if (direction == DIR_DOWN)
    {
        qDebug() << "Down";
    }
    else
    {
        qDebug() << "stay";
    }
}

void Cabin::cabin_stop_slot()
{
    qDebug() << "Stop";
}

Cabin::~Cabin()
{
}
