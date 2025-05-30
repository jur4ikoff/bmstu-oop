#include "floor_button.hpp"
#include "config.h"
#include <QDebug>

FloorButton::FloorButton(int floor, direction_t direction, QWidget *parent)
    : BaseButton(parent), _floor(floor), _direction(direction)
{
    QObject::connect(this, SIGNAL(activate_signal()), this, SLOT(activate_slot()));
    QObject::connect(this, SIGNAL(deactivate_signal()), this, SLOT(deactivate_slot()));
}

void FloorButton::activate_slot()
{
    if (this->_state == BUTTON_ACTIVE)
        return;

    if (_direction == DIR_UP)
    {
        qInfo(TEXT_BLUE "[!] На этаже №%d была нажата кнопка вызова НАВЕРХ." TEXT_DEFAULT, _floor);
    }
    else
    {
        qInfo(TEXT_BLUE "[!] На этаже №%d была нажата кнопка вызова ВНИЗ." TEXT_DEFAULT, _floor);
    }

    emit activated_signal();
}

void FloorButton::deactivate_slot()
{
}
