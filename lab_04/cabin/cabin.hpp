#pragma once

#include "config.h"
#include "constants.hpp"
#include "doors.hpp"

#include <QObject>
#include <QTimer>

class Cabin : public QObject
{
    Q_OBJECT

public:
    Cabin(cabin_id_t id, QObject *parent = nullptr);
    ~Cabin();
    QTimer _move_timer; // TODO заменить памблик таймер на сигнал

signals:
    void cabin_finish_boarding(int floor, cabin_id_t id);

    void cabin_stop();
    void passing_floor();
    void open_doors();

public slots:
    void cabin_free_slot();
    void cabin_moving_slot(direction_t direction);
    void cabin_stop_boarding_slot();
    void cabin_start_boarding_slot();

private:
    cabin_id_t _id;

    enum cabin_state_t
    {
        CAB_FREE,
        CAB_MOVE,
        CAB_BOARDING_STARTED,
        CAB_BOARDING_FINISHED,
    };

    cabin_state_t _state;
    Doors _doors;

    int _cur_floor;
};
