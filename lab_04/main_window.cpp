#include "main_window.h"
#include "constants.hpp"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(WINDOWS_X, WINDOWS_Y);
    this->setWindowTitle("ЛР4 — Лифт");

    QObject::connect(&lift_system, SIGNAL(floor_buttons_change_color_signal(int, direction_t, bool)), this,
                     SLOT(change_floor_button_style_slot(int, direction_t, bool)));

    QObject::connect(&lift_system, SIGNAL(cabin_buttons_change_color_signal(int, cabin_id_t, bool)), this,
                     SLOT(change_cabin_button_style_slot(int, cabin_id_t, bool)));

    QObject::connect(this, SIGNAL(floor_buttons_change_color_signal(int, direction_t, bool)), this,
                     SLOT(change_floor_button_style_slot(int, direction_t, bool)));

    QObject::connect(this, SIGNAL(cabin_buttons_change_color_signal(int, cabin_id_t, bool)), this,
                     SLOT(change_cabin_button_style_slot(int, cabin_id_t, bool)));

    // Берем все кнопки и коннектис их к слотам
    for (int floor = 1; floor <= FLOOR_COUNT; floor++)
    {
        if (floor != FLOOR_COUNT)
        {
            QPushButton *up_button = findChild<QPushButton *>(QString("floor%1_up").arg(floor));
            QObject::connect(up_button, &QPushButton::clicked, [=, this]()
                             { lift_system.manage_floor_call_slot(floor, DIR_UP); });
        }
        if (floor > 1)
        {
            QPushButton *down_button = findChild<QPushButton *>(QString("floor%1_down").arg(floor));
            QObject::connect(down_button, &QPushButton::clicked, [=, this]()
                             { lift_system.manage_floor_call_slot(floor, DIR_DOWN); });
        }

        QPushButton *floor_button = findChild<QPushButton *>(QString("el1_floor%1").arg(floor));
        QObject::connect(floor_button, &QPushButton::clicked, [=, this]()
                         { lift_system.manage_cabin_call_slot(floor, CID_FIRST); });

        floor_button = findChild<QPushButton *>(QString("el2_floor%1").arg(floor));
        QObject::connect(floor_button, &QPushButton::clicked, [=, this]()
                         { lift_system.manage_cabin_call_slot(floor, CID_SECOND); });
    }
}

/// @brief Слот, меняет цвет кнопок на этаже
/// @param floor Этаж
/// @param direction Направление
/// @param is_active
void MainWindow::change_floor_button_style_slot(int floor, direction_t direction, bool is_active)
{
    QPushButton *button = nullptr;
    if (direction == DIR_UP)
    {
        button = findChild<QPushButton *>(QString("floor%1_up").arg(floor));
    }
    else if (direction == DIR_DOWN)
    {
        button = findChild<QPushButton *>(QString("floor%1_down").arg(floor));
    }

    if (button)
    {
        if (is_active)
            button->setStyleSheet(QString("background-color:") + COLOR_ACTIVE_BUTTON);
        else
            button->setStyleSheet(QString("background-color:") + COLOR_INACTIVE_BUTTON);
    }
    this->update();
}

void MainWindow::change_cabin_button_style_slot(int floor, cabin_id_t cabin_id, bool is_active)
{
    QPushButton *button = nullptr;
    if (cabin_id == CID_FIRST)
    {
        button = findChild<QPushButton *>(QString("el1_floor%1").arg(floor));
    }
    else if (cabin_id == CID_SECOND)
    {
        button = findChild<QPushButton *>(QString("el2_floor%1").arg(floor));
    }

    if (button)
    {
        if (is_active)
            button->setStyleSheet(QString("background-color:") + COLOR_ACTIVE_BUTTON);
        else
            button->setStyleSheet(QString("background-color:") + COLOR_INACTIVE_BUTTON);
    }
    this->update();
}

MainWindow::~MainWindow(void)
{
    delete ui;
}
