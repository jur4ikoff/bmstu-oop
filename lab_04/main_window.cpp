#include "main_window.h"
#include "constants.hpp"
#include "ui_main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(WINDOWS_X, WINDOWS_Y);
    this->setWindowTitle("ЛР4 — Лифт");

    // Берем все кнопки и коннектис их к слотам
    for (int floor = 1; floor <= FLOOR_COUNT; floor++)
    {
        if (floor != FLOOR_COUNT)
        {
            QPushButton *up_button = findChild<QPushButton *>(QString("floor%1_up").arg(floor));
            QObject::connect(up_button, &QPushButton::clicked, [=, this]() { elevator_system.manage_floor_call_slot(floor, DIR_UP); });
        }
        if (floor > 1)
        {
            QPushButton *down_button = findChild<QPushButton *>(QString("floor%1_down").arg(floor));
            QObject::connect(down_button, &QPushButton::clicked, [=, this]() { elevator_system.manage_floor_call_slot(floor, DIR_DOWN); });
        }

        QPushButton *floor_button = findChild<QPushButton *>(QString("el1_floor%1").arg(floor));
        QObject::connect(floor_button, &QPushButton::clicked, [=, this]() { elevator_system.manage_cabin_call_slot(floor, CID_FIRST); });

        floor_button = findChild<QPushButton *>(QString("el2_floor%1").arg(floor));
        QObject::connect(floor_button, &QPushButton::clicked, [=, this]() { elevator_system.manage_cabin_call_slot(floor, CID_SECOND); });
    }

    // TODO Привязать изменение цвета на нажатие кнопки 
    // Остановился на 124 строке
}

MainWindow::~MainWindow(void)
{
    delete ui;
}
