#include "controller.hpp"

Controller::Controller(QObject *parent)
    : QObject(parent)
{
    for (int i = 0; i < CABINS_COUNT; i++)
    {
        _cabins[i] = std::make_unique<Cabin>((cabin_id_t)i, this);
        _cur_floor[i] = START_FLOOR - 1;
        _cur_directions[i] = DIR_STAND;
        // TODO BIND
    }

    // TODO BIND

    for (int i = 0; i < FLOOR_COUNT; i++)
    {
        _floor_buttons[BDIR_UP][i] = std::make_shared<FloorButton>(i + 1, DIR_UP);
        _floor_buttons[BDIR_DOWN][i] = std::make_shared<FloorButton>(i + 1, DIR_DOWN);
        _lift_buttons[CID_FIRST][i] = std::make_shared<LiftButton>(i + 1, CID_FIRST);
        _lift_buttons[CID_SECOND][i] = std::make_shared<LiftButton>(i + 1, CID_SECOND);

        // .get() извлекает из этого shared_ptr обычный указатель типа FloorButton*
        QObject::connect(_floor_buttons[BDIR_UP][i].get(), &FloorButton::activated_signal, this, [=]() {
            qDebug() << "test";
            // TODO cabin_id_t id = get_desided_cabin_id(i + 1, DIR_UP);
            // TODO
        });
        QObject::connect(_floor_buttons[BDIR_DOWN][i].get(), &FloorButton::activated_signal, this, [=]() {
            qDebug() << "test";
            // TODO cabin_id_t id = get_desided_cabin_id(i + 1, DIR_UP);
            // TODO
        });

        QObject::connect(_lift_buttons[CID_FIRST][i].get(), &LiftButton::activated_signal, this, [=]() {
            qDebug() << "1";
            // TODO
        });
        QObject::connect(_lift_buttons[CID_SECOND][i].get(), &LiftButton::activated_signal, this, [=]() {
            qDebug() << "2";
            // TODO
        });

        // Сигналы деактивации кнопки нельзя так просто подключать к менеджеру,
        // потому что есть необходимость в отключении нескольких кнопок за раз.
        // В итоге менеджер идет обрабатывать промежуточное состояние,
        // когда одна кнопка отключена, а вторая ещё нет.
        // TODO
        // QObject::connect(this, SIGNAL(buttonsDeactivatedSignal(cabin_id_t)), this, SLOT(manage_cabin_slot(cabin_id_t)));

        QObject::connect(_floor_buttons[BDIR_UP][i].get(), &FloorButton::activated_signal, this, [=, this]() {
            color_floor_button_change(i + 1, DIR_UP, true);
        });
        QObject::connect(_floor_buttons[BDIR_DOWN][i].get(), &FloorButton::activated_signal, this, [=, this]() {
            color_floor_button_change(i + 1, DIR_DOWN, true);
        });
        QObject::connect(_lift_buttons[CID_FIRST][i].get(), &LiftButton::activated_signal, this, [=, this]() {
            color_cabin_button_change(i + 1, CID_FIRST, true);
        });
        QObject::connect(_lift_buttons[CID_SECOND][i].get(), &LiftButton::activated_signal, this, [=, this]() {
            color_cabin_button_change(i + 1, CID_SECOND, true);
        });

        QObject::connect(_floor_buttons[BDIR_UP][i].get(), &FloorButton::deactivated_signal, this, [=, this]() {
            color_floor_button_change(i + 1, DIR_UP, false);
        });
        QObject::connect(_floor_buttons[BDIR_DOWN][i].get(), &FloorButton::deactivated_signal, this, [=, this]() {
            color_floor_button_change(i + 1, DIR_DOWN, false);
        });
        QObject::connect(_lift_buttons[CID_FIRST][i].get(), &LiftButton::deactivated_signal, this, [=, this]() {
            color_cabin_button_change(i + 1, CID_FIRST, false);
        });
        QObject::connect(_lift_buttons[CID_SECOND][i].get(), &LiftButton::deactivated_signal, this, [=, this]() {
            color_cabin_button_change(i + 1, CID_SECOND, false);
        });

        // TODO
        //     QObject::connect(this, SIGNAL(freeControllerSignal()), this, SLOT(free_controller_slot()));
    }
    qDebug() << "controller Init";
}

void Controller::floor_destanation_slot(int floor, direction_t direction)
{
    if (direction == DIR_DOWN)
    {
        qDebug() << "Call down from " << floor;
    }
    else if (direction == DIR_UP)
    {
        qDebug() << "Call up from " << floor;
    }
}

void Controller::cabin_destanation_slot(int floor, cabin_id_t id)
{
    if (to_visit[id][TO_VISIT_ANY][floor - 1])
        return;

    _state = CON_REQUEST;
    to_visit[id][TO_VISIT_ANY][floor - 1] = true;

    emit _lift_buttons[id][floor - 1]->activate_signal();

    // if (id == CID_FIRST)
    // {
    //     qDebug() << "Call " << floor << "floor in 1 elevator";
    // }
    // else if (id == CID_SECOND)
    // {
    //     qDebug() << "Call " << floor << "floor in 2 elevator";
    // }

    // emit cabin_buttons_change_color_signal(1, CID_FIRST, 1);
}

void Controller::color_floor_button_change(int floor, direction_t direction, bool is_active)
{
    emit floor_buttons_change_color_signal(floor, direction, is_active);
}

void Controller::color_cabin_button_change(int floor, cabin_id_t id, bool is_active)
{
    emit cabin_buttons_change_color_signal(floor, id, is_active);
}

Controller::~Controller()
{
}
