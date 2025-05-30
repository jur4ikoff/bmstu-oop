#pragma once

#include "controller.hpp"

#include "constants.hpp"
#include "config.h"

#include <QObject>

class liftSystem : public QObject
{
    Q_OBJECT

public:
    explicit liftSystem(QObject *parent = nullptr);

signals:
    // Сигналы, испускаемые для изменения окраски кнопки
    void floor_buttons_change_color_signal(int, direction_t, bool);
    void cabin_buttons_change_color_signal(int, cabin_id_t, bool);

    // Сигналы, испускаемые при нажатии кнопки
    void from_floor_call_signal(int floor, direction_t direction);
    void from_cabin_call_signal(int floor, cabin_id_t id);

public slots:
    void manage_floor_call_slot(int floor, direction_t direction);
    void manage_cabin_call_slot(int floor, cabin_id_t id);

private:
    // Состояния подъемной системы
    Controller _controller;
};
