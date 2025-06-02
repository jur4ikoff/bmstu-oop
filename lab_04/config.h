#pragma once

#define FLOOR_COUNT 8
#define CABINS_COUNT 2

#define START_FLOOR 1

#define COLOR_ACTIVE_BUTTON "#00FF00"
#define COLOR_INACTIVE_BUTTON "#606060"

#define TEXT_GREEN "\033[0;32m"
#define TEXT_CYAN "\033[0;36m"
#define TEXT_BLUE "\033[0;34m"

#define TEXT_DEFAULT "\033[0m"

#define DIRECTIONS_COUNT 2

#define WAIT_TIME 1200
#define MOVE_TIME 1200
#define DOOR_OPENING_AFTER_CLOSING 800

enum direction_t
{
    DIR_DOWN = -1,
    DIR_STAND = 0,
    DIR_UP = 1
};

enum button_direction_t
{
    BDIR_UP,
    BDIR_DOWN,
};

enum cabin_id_t

{
    CID_FIRST,
    CID_SECOND
};

enum to_visit_t
{
    TO_VISIT_UP,
    TO_VISIT_DOWN,
    TO_VISIT_ANY,
    TO_VISIT_COUNT,
};
