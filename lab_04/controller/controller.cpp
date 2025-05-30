#include "controller.hpp"

Controller::Controller(QObject *parent)
    : QObject(parent)
{
    for (int i = 0; i < N_CABINS; i++)
    {
        cabin[i] = std::make_unique<Cabin>((cabin_id_t)i, this);
    }
    qDebug() << "controller Init";
}

void Controller::floor_destanation_slot(int floor, direction_t direction)
{
    if (direction == DIR_DOWN)
    {
        qDebug() << "Call down from " << floor;
    }
    else if (direction == DIR_UP)
    {
        qDebug() << "Call up from " << floor;
    }
}

void Controller::cabin_destanation_slot(int floor, cabin_id_t id)
{
    if (id == CID_FIRST)
    {
        qDebug() << "Call " << floor << "floor in 1 elevator";
    }
    else if (id == CID_SECOND)
    {
        qDebug() << "Call " << floor << "floor in 2 elevator";
    }

    emit cabin_buttons_change_color_signal(1, CID_FIRST, 1);
}

Controller::~Controller()
{
}
