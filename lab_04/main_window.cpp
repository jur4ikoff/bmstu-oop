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
    // this->setFixedSize(WINDOWS_X, WINDOWS_Y);
    this->setFixedSize(800, 781);
}

MainWindow::~MainWindow(void)
{
    delete ui;
}
