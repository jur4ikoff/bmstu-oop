#include "doors.hpp"

Doors::Doors(cabin_id_t id, QObject *parent)
    : QObject(parent), _id(id), _state(DOOR_CLOSED)
{
    open_door_timer.setSingleShot(true);
    open_state_door_timer.setSingleShot(true);
    close_door_timer.setSingleShot(true);

    QObject::connect(&open_door_timer, SIGNAL(timeout()), this, SLOT(open_slot()));
    QObject::connect(&open_state_door_timer, SIGNAL(timeout()), this, SLOT(start_closing_slot()));
    QObject::connect(&close_door_timer, SIGNAL(timeout()), this, SLOT(close_slot()));
    qDebug() << "Init doors";
}

void Doors::start_opening_slot()
{
    if (_state != DOOR_CLOSED)
        return;

    _state = DOOR_OPENING;
    qInfo(TEXT_GREEN "[*] Двери лифта №%d открываются..." TEXT_DEFAULT, _id + 1);
    open_door_timer.start(WAIT_TIME);
}

void Doors::start_closing_slot()
{
    if (_state != DOOR_OPENED)
        return;

    _state = DOOR_CLOSING;
    qInfo(TEXT_GREEN "[*] Двери лифта №%d закрываются..." TEXT_DEFAULT, _id + 1);
    close_door_timer.start(WAIT_TIME);
}

void Doors::open_slot()
{
    if (_state != DOOR_OPENING)
        return;

    _state = DOOR_OPENED;
    qInfo(TEXT_GREEN "[*] Двери лифта №%d открылись." TEXT_DEFAULT, _id + 1);
    open_state_door_timer.start(WAIT_TIME);
}

void Doors::close_slot()
{
    if (_state != DOOR_CLOSING)
        return;

    _state = DOOR_CLOSED;
    qInfo(TEXT_GREEN "[*] Двери лифта №%d закрылись." TEXT_DEFAULT, _id + 1);
    emit door_is_closed();
}
