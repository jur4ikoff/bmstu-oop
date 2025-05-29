#pragma once

// #include "controller.hpp"
#include "constants.hpp"
#include <QObject>

class ElevatorSystem : public QObject
{
    Q_OBJECT

public:
    explicit ElevatorSystem(QObject *parent = nullptr);

public slots:
    void manage_floor_call_slot(int floor, direction_t direction);
    void manage_cabin_call_slot(int floor, cabin_id_t cabin_id);

private:
    // Состояния подъемной системы
    enum elevator_system_state_t
    {
        ELSYS_FREE,
        ELSYS_CABIN_CALL,
        ELSYS_MANAGING_FLOOOR_CALL
    };

    elevator_system_state_t _state;
};
