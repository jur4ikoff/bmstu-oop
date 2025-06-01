#include "cabin.hpp"

Cabin::Cabin(cabin_id_t id, QObject *parent)
    : QObject(parent), _id(id), _state(CAB_BOARDING_FINISHED), _doors(id), _cur_floor(START_FLOOR)
{
    _move_timer.setSingleShot(true);
    // QObject::connect(this, SIGNAL(cabin_stop()), this, SLOT(cabin_start_boarding_slot())); // TODO Нет такого сигнала
    QObject::connect(this, SIGNAL(open_doors()), &_doors, SLOT(start_opening_slot()));
    QObject::connect(&_doors, SIGNAL(door_is_closed()), this, SLOT(cabin_stop_boarding_slot()));
}

void Cabin::cabin_free_slot()
{
    // TODO check_condition
    if (_state != CAB_BOARDING_STARTED)
        return;
    
    _state = CAB_FREE;
}

void Cabin::cabin_moving_slot(direction_t direction)
{
    if (_state == CAB_BOARDING_STARTED)
        return;

    _state = CAB_MOVE;

    if (direction == DIR_UP)
    {
        qInfo("[!] Лифт №%d едет c этажа №%d на этаж №%d.", _id + 1, _cur_floor, _cur_floor + 1);
        _cur_floor++;
        _move_timer.start(MOVE_TIME);
    }
    else if (direction == DIR_DOWN)
    {
        qInfo("[!] Лифт №%d едет c этажа №%d на этаж №%d.", _id + 1, _cur_floor, _cur_floor - 1);
        _cur_floor--;
        _move_timer.start(MOVE_TIME);
    }
}

void Cabin::cabin_start_boarding_slot()
{
    if (_state == CAB_BOARDING_STARTED)
        return;

    _state = CAB_BOARDING_STARTED;
    qInfo("Лифт №%d остановился на этаже №%d.", _id + 1, _cur_floor);
    _cur_floor++;
    emit open_doors();
}

void Cabin::cabin_stop_boarding_slot()
{
    if (_state == CAB_BOARDING_FINISHED)
        return;

    _state = CAB_BOARDING_FINISHED;
    qInfo("Посадка/высадка пассажиров в лифте №%d завершена.", _id + 1);
    emit cabin_finish_boarding(_cur_floor, _id);
}

Cabin::~Cabin()
{
}
