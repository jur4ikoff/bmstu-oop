#include "lift.hpp"

LiftSystem::LiftSystem(QObject *parent)
    : QObject(parent)
{
    QObject::connect(this, SIGNAL(floor_destanation_slot(int, direction_t)), &_controller, SLOT(floor_destanation_slot(int, direction_t)));
    QObject::connect(this, SIGNAL(cabin_destanation_slot(int, cabin_id_t)), &_controller, SLOT(cabin_destanation_slot(int, cabin_id_t)));

    QObject::connect(&_controller, SIGNAL(floor_buttons_change_color_signal(int, direction_t, bool)), this, SLOT(change_floor_button_style_slot(int, direction_t, bool)));
    QObject::connect(&_controller, SIGNAL(cabin_buttons_change_color_signal(int, cabin_id_t, bool)), this, SLOT(change_cabin_button_style_slot(int, cabin_id_t, bool)));
}

void LiftSystem::manage_floor_call_slot(int floor, direction_t direction)
{
    emit floor_destanation_slot(floor, direction);
}

void LiftSystem::manage_cabin_call_slot(int floor, cabin_id_t id)
{
    emit cabin_destanation_slot(floor, id);
}

void LiftSystem::change_floor_button_style_slot(int floor, direction_t direction, bool is_active)
{
    emit floor_buttons_change_color_signal(floor, direction, is_active);
}

void LiftSystem::change_cabin_button_style_slot(int floor, cabin_id_t id, bool is_active)
{
    emit cabin_buttons_change_color_signal(floor, id, is_active);
}
