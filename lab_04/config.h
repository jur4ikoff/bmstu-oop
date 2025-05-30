#pragma once

#define FLOOR_COUNT 8
#define CABINS_COUNT 2

#define START_FLOOR

#define COLOR_ACTIVE_BUTTON "#00FF00"
#define COLOR_INACTIVE_BUTTON "#606060"


#define TEXT_GREEN "\033[0;32m"
#define TEXT_BLUE "\033[0;34m"
#define TEXT_DEFAULT "\033[0m"


#define DIRECTIONS_COUNT 2
enum direction_t
{
    DIR_DOWN = -1,
    DIR_STAND = 0,
    DIR_UP = 1
};

enum cabin_id_t
{
    CID_FIRST,
    CID_SECOND
};
