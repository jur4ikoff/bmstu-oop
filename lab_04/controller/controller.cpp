#include "controller.hpp"

#define FLOOR_NOT_FOUND -1

// ЛИФТ ОСТАНАВЛИВАЕТСЯ НА КАЖДОМ ЭТАЖЕ

Controller::Controller(QObject *parent)
    : QObject(parent)
{
    for (int i = 0; i < CABINS_COUNT; i++)
    {
        _cabins[i] = std::make_unique<Cabin>((cabin_id_t)i, this);
        _cur_floor[i] = START_FLOOR - 1;
        _cur_directions[i] = DIR_STAND;

        QObject::connect(_cabins[i].get(), &Cabin::cabin_finish_boarding, this, &Controller::reach_dst_floor_slot);
        QObject::connect(&_cabins[i]->move_timer, &QTimer::timeout, this, [=, this]()
                         { manage_cabin_slot(static_cast<cabin_id_t>(i)); });
    }

    QObject::connect(this, &Controller::manage_move_signal, this, [this](cabin_id_t id, direction_t direction)
                     { manage_move_slot(static_cast<cabin_id_t>(id), direction); });
    QObject::connect(this, &Controller::free_cabin_signal, this, [this](cabin_id_t id)
                     { _cabins[id]->cabin_free_slot(); });
    QObject::connect(this, &Controller::move_cabin_signal, this, [this](cabin_id_t id, direction_t direction)
                     { _cabins[id]->cabin_moving_slot(direction); });
    QObject::connect(this, &Controller::stop_cabin_signal, this, [this](cabin_id_t id)
                     { _cabins[id]->cabin_start_boarding_slot(); });

    for (int i = 0; i < FLOOR_COUNT; i++)
    {
        _floor_buttons[BDIR_UP][i] = std::make_shared<FloorButton>(i + 1, DIR_UP);
        _floor_buttons[BDIR_DOWN][i] = std::make_shared<FloorButton>(i + 1, DIR_DOWN);
        _lift_buttons[CID_FIRST][i] = std::make_shared<LiftButton>(i + 1, CID_FIRST);
        _lift_buttons[CID_SECOND][i] = std::make_shared<LiftButton>(i + 1, CID_SECOND);

        QObject::connect(_floor_buttons[BDIR_UP][i].get(), &FloorButton::activated_signal, this, [=, this]()
                         {
            cabin_id_t id = get_desided_cabin_id(i, DIR_UP);
            manage_cabin_slot(id); });
        QObject::connect(_floor_buttons[BDIR_DOWN][i].get(), &FloorButton::activated_signal, this, [=, this]()
                         {
            cabin_id_t id = get_desided_cabin_id(i, DIR_DOWN);
            manage_cabin_slot(id); });

        QObject::connect(_lift_buttons[CID_FIRST][i].get(), &LiftButton::activated_signal, this, [=, this]()
                         { manage_cabin_slot(CID_FIRST); });
        QObject::connect(_lift_buttons[CID_SECOND][i].get(), &LiftButton::activated_signal, this, [=, this]()
                         { manage_cabin_slot(CID_SECOND); });

        // Сигналы деактивации кнопки нельзя так просто подключать к менеджеру,
        // потому что есть необходимость в отключении нескольких кнопок за раз.
        // В итоге менеджер идет обрабатывать промежуточное состояние,
        // когда одна кнопка отключена, а вторая ещё нет.
        QObject::connect(this, SIGNAL(button_deactivated_signal(cabin_id_t)), this, SLOT(manage_cabin_slot(cabin_id_t)));

        QObject::connect(_floor_buttons[BDIR_UP][i].get(), &FloorButton::activated_signal, this, [=, this]()
                         { emit floor_buttons_change_color_signal(i + 1, DIR_UP, true); });
        QObject::connect(_floor_buttons[BDIR_DOWN][i].get(), &FloorButton::activated_signal, this, [=, this]()
                         { emit floor_buttons_change_color_signal(i + 1, DIR_DOWN, true); });
        QObject::connect(_lift_buttons[CID_FIRST][i].get(), &LiftButton::activated_signal, this, [=, this]()
                         { emit cabin_buttons_change_color_signal(i + 1, CID_FIRST, true); });
        QObject::connect(_lift_buttons[CID_SECOND][i].get(), &LiftButton::activated_signal, this, [=, this]()
                         { emit cabin_buttons_change_color_signal(i + 1, CID_SECOND, true); });

        QObject::connect(_floor_buttons[BDIR_UP][i].get(), &FloorButton::deactivated_signal, this, [=, this]()
                         { emit floor_buttons_change_color_signal(i + 1, DIR_UP, false); });
        QObject::connect(_floor_buttons[BDIR_DOWN][i].get(), &FloorButton::deactivated_signal, this, [=, this]()
                         { emit floor_buttons_change_color_signal(i + 1, DIR_DOWN, false); });
        QObject::connect(_lift_buttons[CID_FIRST][i].get(), &LiftButton::deactivated_signal, this, [=, this]()
                         { emit cabin_buttons_change_color_signal(i + 1, CID_FIRST, false); });
        QObject::connect(_lift_buttons[CID_SECOND][i].get(), &LiftButton::deactivated_signal, this, [=, this]()
                         { emit cabin_buttons_change_color_signal(i + 1, CID_SECOND, false); });

        QObject::connect(this, SIGNAL(free_contoller_signal()), this, SLOT(free_controller_slot()));
    }
}

// Слот вызывается, при нажатии на кнопку вызова на этаже
void Controller::floor_destanation_slot(int floor, direction_t direction)
{
    qDebug() << "tut";
    if (_state != CON_FREE && _state != CON_MANAGING_CABIN && _state != CON_MANAGING_MOVE)
        return;

    // Если кабина уже едет на этаж, то выходим
    for (int id = 0; id < CABINS_COUNT; id++)
    {
        if ((direction == DIR_DOWN && _to_visit[id][TO_VISIT_DOWN][floor - 1]) ||
            (direction == DIR_UP && _to_visit[id][TO_VISIT_UP][floor - 1]))
        {
            return;
        }
    }

    _state = CON_REQUEST_FLOOR;

    cabin_id_t desided_cabin_id = CID_FIRST;
    int min_dst = FLOOR_COUNT + 1;

    // Из всех кабин, котороые свободны или едут в направлени нужного этажа, выбираем ближайшую
    for (int i = 0; i < CABINS_COUNT; i++)
    {
        int cur_distance = floor - _cur_floor[i];
        direction_t move_direction = get_direction(cur_distance);
        cur_distance = std::abs(cur_distance);

        // Нужно нужно вверх (вниз), кабина ниже (выше)
        if (_cur_directions[i] == DIR_STAND || (move_direction == _cur_directions[i] && direction == _cur_directions[i]))
        {
            if (cur_distance < min_dst)
            {
                min_dst = cur_distance;
                desided_cabin_id = static_cast<cabin_id_t>(i);
            }
        }
    }

    // В остальных случаях, выбираем ту кабину, которая свободнее
    if (min_dst == FLOOR_COUNT + 1)
    {
        int min_visits_count = FLOOR_COUNT;
        for (int i = 0; i < CABINS_COUNT; i++)
        {
            int cur_visits_count = 0;
            for (int j = 0; j < CABINS_COUNT; j++)
            {
                if (_to_visit[i][TO_VISIT_ANY][j] || _to_visit[i][TO_VISIT_UP][j] || _to_visit[i][TO_VISIT_DOWN][j])
                {
                    cur_visits_count++;
                }
            }

            if (cur_visits_count < min_visits_count)
            {
                min_visits_count = cur_visits_count;
                desided_cabin_id = static_cast<cabin_id_t>(i);
            }
        }
    }

    if (direction == DIR_UP)
    {
        _to_visit[desided_cabin_id][TO_VISIT_UP][floor - 1] = true;
        emit _floor_buttons[BDIR_UP][floor - 1]->activate_signal();
    }
    else
    {
        _to_visit[desided_cabin_id][TO_VISIT_DOWN][floor - 1] = true;
        emit _floor_buttons[BDIR_DOWN][floor - 1]->activate_signal();
    }
}

// Слот вызывается при нажатии на кнопку в кабине
void Controller::cabin_destanation_slot(int floor, cabin_id_t id)
{
    if (_state != CON_FREE && _state != CON_MANAGING_CABIN && _state != CON_MANAGING_MOVE)
        return;

    if (_to_visit[id][TO_VISIT_ANY][floor - 1])
        return;

    _state = CON_REQUEST_CABIN;
    _to_visit[id][TO_VISIT_ANY][floor - 1] = true;

    emit _lift_buttons[id][floor - 1]->activate_signal();
}

void Controller::manage_move_slot(cabin_id_t id, direction_t direction)
{
    if (_state != CON_MANAGING_CABIN)
        return;

    _state = CON_MANAGING_MOVE;

    _cur_directions[id] = direction;
    _cur_floor[id] += direction;
    emit move_cabin_signal(id, direction);
}

// Основная функция управления кабиной
void Controller::manage_cabin_slot(cabin_id_t id)
{
    if (_state == CON_FREE || _state == CON_MANAGING_CABIN)
        return;

    _state = CON_MANAGING_CABIN;

    int dst_floor = get_next_visit_floor(id);
    if (dst_floor == FLOOR_NOT_FOUND)
    {
        _cur_directions[id] = DIR_STAND;
        emit free_cabin_signal(id);
    }
    else if (dst_floor > _cur_floor[id])
    {
        emit manage_move_signal(id, DIR_UP);
    }
    else if (dst_floor < _cur_floor[id])
    {
        emit manage_move_signal(id, DIR_DOWN);
    }
    else
    {
        _cur_directions[id] = get_next_direction(id);
        emit stop_cabin_signal(id);
    }

    if (is_all_cabins_are_free())
        emit free_contoller_signal();
}

// Слот обрабатывает достижение этажа
void Controller::reach_dst_floor_slot(int floor, cabin_id_t id)
{
    if (_state != CON_MANAGING_CABIN)
        return;

    _state = CON_REACH_DST_FLOOR;

    _to_visit[id][TO_VISIT_ANY][floor - 1] = false;
    emit _lift_buttons[id][floor - 1]->deactivate_signal();

    if (_cur_directions[id] == DIR_UP)
    {
        _to_visit[id][TO_VISIT_UP][floor - 1] = false;
        emit _floor_buttons[BDIR_UP][floor - 1]->deactivate_signal();
    }
    else
    {
        _to_visit[id][TO_VISIT_DOWN][floor - 1] = false;
        emit _floor_buttons[BDIR_DOWN][floor - 1]->deactivate_signal();
    }

    emit button_deactivated_signal(id);
}

void Controller::free_controller_slot()
{
    if (_state == CON_FREE)
        return;

    _state = CON_FREE;
    qInfo("[!] Контроллер находится в состоянии покоя.");
}

direction_t Controller::get_direction(int difference)
{
    if (difference == 0)
    {
        return DIR_STAND;
    }

    return difference > 0 ? DIR_UP : DIR_DOWN;
}

cabin_id_t Controller::get_desided_cabin_id(int floor, direction_t direction)
{
    for (int i = 0; i < CABINS_COUNT; i++)
    {
        if ((direction == DIR_UP && _to_visit[i][TO_VISIT_UP][floor]) ||
            (direction == DIR_DOWN && _to_visit[i][TO_VISIT_DOWN][floor]))
            return static_cast<cabin_id_t>(i);
    }
    return CID_FIRST;
}

// Вычисление этажа на который (следующим) поедет кабина
int Controller::get_next_visit_floor(cabin_id_t id)
{
    int dst_floor = FLOOR_NOT_FOUND;

    if (_cur_directions[id] == DIR_STAND)
    {
        // Если лифт стоит, то едет к ближайшему этажу
        int min_dst = FLOOR_COUNT;

        for (int i = 0; i < FLOOR_COUNT; i++)
        {
            if (_to_visit[id][TO_VISIT_ANY][i] || _to_visit[id][TO_VISIT_UP][i] || _to_visit[id][TO_VISIT_DOWN][i])
            {
                int diff = _cur_floor[id] - i;
                if (diff < min_dst)
                {
                    min_dst = diff;
                    dst_floor = i;
                }
            }
        }
    }
    else
    {
        for (int i = _cur_floor[id]; i >= 0 && i < FLOOR_COUNT; i += _cur_directions[id])
        {
            // Ищем этажи по ходу движения
            if (_cur_directions[id] == DIR_UP)
            {
                if (_to_visit[id][TO_VISIT_ANY][i] || _to_visit[id][TO_VISIT_UP][i])
                    return i;
            }
            else
            {
                if (_to_visit[id][TO_VISIT_ANY][i] || _to_visit[id][TO_VISIT_DOWN][i])
                    return i;
            }
        }

        // Ищем в обратном направлении
        if (_cur_directions[id] == DIR_UP)
        {
            for (int i = FLOOR_COUNT - 1; i >= 0; i--)
            {
                if (_to_visit[id][TO_VISIT_DOWN][i])
                    return i;
            }
        }
        if (_cur_directions[id] == DIR_DOWN)
        {
            for (int i = 0; i < FLOOR_COUNT; i++)
            {
                if (_to_visit[id][TO_VISIT_UP][i])
                    return i;
            }
        }
    }

    return dst_floor;
}

// Вычесление следующего направления
direction_t Controller::get_next_direction(cabin_id_t id)
{
    if (_cur_directions[id] == DIR_STAND)
    {
        // Если лифт стоит, то едем к ближнему этажу
        int dst_visit_floor = -1;
        int min_dst = FLOOR_COUNT;

        for (int i = 0; i < FLOOR_COUNT; i++)
        {
            if (_to_visit[id][TO_VISIT_ANY][i] || _to_visit[id][TO_VISIT_UP][i] || _to_visit[id][TO_VISIT_DOWN][i])
            {
                int diff = _cur_floor[id] - i;
                diff = std::abs(diff);

                if (diff && diff < min_dst)
                {
                    min_dst = diff;
                    dst_visit_floor = i;
                }
            }
        }

        if (min_dst == FLOOR_COUNT)
            return DIR_STAND;

        if (dst_visit_floor > _cur_floor[id])
            return DIR_UP;
        else
            return DIR_DOWN;
    }

    for (int i = _cur_floor[id] + _cur_directions[id]; i >= 0 && i < FLOOR_COUNT; i += _cur_directions[id])
    {
        // Ищем желающих поехать по ходу движения кабины, к которым можно заехать в текущем её положении.
        if (_cur_directions[id] == DIR_UP)
        {
            if (_to_visit[id][TO_VISIT_ANY][i] || _to_visit[id][TO_VISIT_UP][i])
                return DIR_UP;
        }
        else
        {
            if (_to_visit[id][TO_VISIT_ANY][i] || _to_visit[id][TO_VISIT_DOWN][i])
                return DIR_DOWN;
        }
    }

    // По ходу движения кабины не нашлось желающих ехать в том же направлении.
    // Не меняем направление кабины, смотрим, есть ли те, кому надо в противоположном направлении.
    // Выбираем самого далёкого из них, чтобы остальных забрать уже по ходу движения.
    if (_cur_directions[id] == DIR_UP)
    {
        for (int i = FLOOR_COUNT - 1; i >= 0; i--)
        {
            if (_to_visit[id][TO_VISIT_DOWN][i])
            {
                // Если найденный этаж равен этажу текущему, пропускаем, потому что мы только что на нем остановились.
                if (i > _cur_floor[id])
                    return DIR_UP;
                else if (i < _cur_floor[id])
                    return DIR_DOWN;
            }
        }
    }

    if (_cur_directions[id] == DIR_DOWN)
    {
        for (int i = 0; i < FLOOR_COUNT; i++)
        {
            if (_to_visit[id][TO_VISIT_UP][i])
            {
                // Если найденный этаж равен этажу текущему, пропускаем, потому что мы только что на нем остановились.
                if (i > _cur_floor[id])
                    return DIR_UP;
                else if (i < _cur_floor[id])
                    return DIR_DOWN;
            }
        }
    }

    // Больше целевых этажей нет, в приоритет ставим направление по ходу движения
    if ((_to_visit[id][TO_VISIT_UP][_cur_floor[id]] || _to_visit[id][TO_VISIT_ANY][_cur_floor[id]]) &&
        _cur_directions[id] == DIR_UP)
        return DIR_UP;

    if ((_to_visit[id][TO_VISIT_DOWN][_cur_floor[id]] || _to_visit[id][TO_VISIT_ANY][_cur_floor[id]]) &&
        _cur_directions[id] == DIR_DOWN)
        return DIR_DOWN;

    // Можно поехать только против хода движения
    return _cur_directions[id] == DIR_UP ? DIR_DOWN : DIR_UP;
}

bool Controller::is_all_cabins_are_free()
{
    for (int i = 0; i < CABINS_COUNT; i++)
    {
        for (int j = 0; j < FLOOR_COUNT; j++)
        {
            if (_to_visit[i][TO_VISIT_ANY][j] || _to_visit[i][TO_VISIT_UP][j] ||
                _to_visit[i][TO_VISIT_DOWN][j])
            {
                return false;
            }
        }
    }

    return true;
}

Controller::~Controller()
{
}
