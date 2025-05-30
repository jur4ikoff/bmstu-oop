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

private:
    int _id;
    // enum cabin_state_t
    // {
    //     CAB_FREE,
    //     CAB_UP,
    //     CAB_DOWN,
    //     CAB_BOARDING_STARTED,
    //     CAB_BOARDING_FINISHED,
    // }
};
