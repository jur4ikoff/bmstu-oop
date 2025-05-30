#pragma once

#include "config.h"
#include "constants.hpp"
#include "cabin.hpp"

#include <QObject>
#include <iostream>

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

signals:
    void floor_buttons_change_color_signal(int, direction_t, bool);
    void cabin_buttons_change_color_signal(int, cabin_id_t, bool);

public slots:
    void floor_destanation_slot(int floor, direction_t direction);
    void cabin_destanation_slot(int floor, cabin_id_t id);

private:
    enum controller_state_t
    {
        CON_FREE,
        CON_REQUEST,
        CON_BUSY,
    };

    std::unique_ptr<Cabin> cabin[N_CABINS] = {};
};
