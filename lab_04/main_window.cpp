#include "main_window.h"
#include "constants.hpp"
#include "ui_main_window.h"

static double to_radians(const double &angle)
{
    return angle * (PI / 180);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(WINDOWS_X, WINDOWS_Y);
    this->setWindowTitle("ЛР4 — Лифт");

    for (int floor = 1; floor <= FLOOR_COUNT; ++floor)
    {
        if (floor != FLOOR_COUNT)
        {
            QPushButton *up_button = findChild<QPushButton *>(QString("floor%1_up").arg(floor));
            QObject::connect(up_button, &QPushButton::clicked, [=, this]()
                             { elevator_system.manage_floor_call_slot(floor, DIR_UP); });
        }
        if (floor > 1)
        {
            QPushButton *down_button = findChild<QPushButton *>(QString("floor%1_down").arg(floor));
            QObject::connect(down_button, &QPushButton::clicked, [=, this]()
                             { elevator_system.manage_floor_call_slot(floor, DIR_DOWN); });
        }

        //     QPushButton *downBtn = findChild<QPushButton *>(QString("floor%1_down").arg(floor));
        //     QPushButton *el1Btn = findChild<QPushButton *>(QString("el1_floor%1").arg(floor));
        //     QPushButton *el2Btn = findChild<QPushButton *>(QString("el2_floor%1").arg(floor));

        //     connect(downBtn, &QPushButton::clicked, [this, floor]()
        //             { handleFloorDown(floor); });
        //     connect(el1Btn, &QPushButton::clicked, [this, floor]()
        //             { handleEl1Floor(floor); });
        //     connect(el2Btn, &QPushButton::clicked, [this, floor]()
        //             { handleEl2Floor(floor); });
    }
}

void MainWindow::handleFloorUp(int floor)
{
    qDebug() << "Floor" << floor << "UP button pressed";
}

void MainWindow::handleFloorDown(int floor)
{
    qDebug() << "Floor" << floor << "DOWN button pressed";
}

MainWindow::~MainWindow(void)
{
    delete ui;
}
