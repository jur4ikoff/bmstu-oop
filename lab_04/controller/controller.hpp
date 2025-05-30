#pragma once

#include "cabin.hpp"
#include "config.h"
#include "constants.hpp"
#include "floor_button.hpp"
#include "lift_button.hpp"

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

    std::unique_ptr<Cabin> _cabins[CABINS_COUNT] = {};
    int _cur_floor[CABINS_COUNT] = {};
    direction_t _cur_directions[CABINS_COUNT] = {};

    std::shared_ptr<FloorButton> _floor_buttons[DIRECTIONS_COUNT][FLOOR_COUNT];
    // std::shared_ptr<LiftButton> _lift_button[CABINS_COUNT][FLOOR_COUNT];
};
