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
    void color_floor_button_change(int floor, direction_t direction, bool is_active);
    void color_cabin_button_change(int floor, cabin_id_t id, bool is_active);

    enum controller_state_t
    {
        CON_FREE,
        CON_REQUEST,
        CON_BUSY,
    };

    controller_state_t _state = CON_FREE;

    std::unique_ptr<Cabin> _cabins[CABINS_COUNT] = {};
    int _cur_floor[CABINS_COUNT] = {};
    direction_t _cur_directions[CABINS_COUNT] = {};

    std::shared_ptr<FloorButton> _floor_buttons[DIRECTIONS_COUNT][FLOOR_COUNT];
    std::shared_ptr<LiftButton> _lift_buttons[CABINS_COUNT][FLOOR_COUNT];

    bool to_visit[CABINS_COUNT][TO_VISIT_COUNT][FLOOR_COUNT] = {};
};
