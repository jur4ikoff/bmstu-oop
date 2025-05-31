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

    void button_deactivated_signal(cabin_id_t);
    void free_cabin_signal(cabin_id_t);
    void move_cabin_signal(cabin_id_t, direction_t);
    void stop_cabin_signal(cabin_id_t);

    void free_contoller_signal();

public slots:
    void floor_destanation_slot(int floor, direction_t direction);
    void cabin_destanation_slot(int floor, cabin_id_t id);

    void color_floor_button_change_slot(int floor, direction_t direction, bool is_active);
    void color_cabin_button_change_slot(int floor, cabin_id_t id, bool is_active);

    void manage_cabin_slot(cabin_id_t cabin_id);

    void reach_floor_slot(int floor, cabin_id_t id);
    void free_controller_slot();

private:
    direction_t get_direction(int difference);
    direction_t get_next_direction(cabin_id_t id);
    cabin_id_t get_desided_cabin_id(int floor, direction_t direction);

    int get_next_visit_floor(cabin_id_t id);
    bool is_all_cabins_are_free();

    enum controller_state_t
    {
        CON_FREE,
        CON_REQUEST,
        CON_MANAGING_CABIN,
        CON_REACH_FLOOR,
    };

    controller_state_t _state = CON_FREE;

    std::unique_ptr<Cabin> _cabins[CABINS_COUNT] = {};
    int _cur_floor[CABINS_COUNT] = {};
    direction_t _cur_directions[CABINS_COUNT] = {};

    std::shared_ptr<FloorButton> _floor_buttons[DIRECTIONS_COUNT][FLOOR_COUNT];
    std::shared_ptr<LiftButton> _lift_buttons[CABINS_COUNT][FLOOR_COUNT];

    bool _to_visit[CABINS_COUNT][TO_VISIT_COUNT][FLOOR_COUNT] = {};
};
