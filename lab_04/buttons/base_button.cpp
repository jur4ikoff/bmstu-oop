#include "base_button.hpp"

BaseButton::BaseButton(QWidget *parent)
    : QObject(parent)
{
    _state = BUTTON_INACTIVE;
}