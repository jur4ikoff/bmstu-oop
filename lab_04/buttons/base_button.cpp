#include "base_button.hpp"

BaseButton::BaseButton(QWidget *parent)
    : QPushButton(parent)
{
    _state = BUTTON_INACTIVE;
}