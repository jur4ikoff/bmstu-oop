#include "main_window.h"
#include "ui_main_window.h"

#include <QDebug>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(1275, 820);

    // инициализируем систему координат
    // CoordSystem *coordinate_system = new CoordSystem(points_1, points_2, solve, solve_cur, ui->ChartWidget);
    // coordinate_system->setGeometry(ui->ChartWidget->geometry());

    // Ставим плейсхолдеры в текст
    // ui->InputX->setPlaceholderText("Введите координату x");
    // ui->InputY->setPlaceholderText("Введите координату y");

    // Биндим кнопки
    // connect(ui->addPoint, &QPushButton::clicked, this, &MainWindow::buttonPushAddPoint);
    // connect(ui->pushButtonDeleteAll, &QPushButton::clicked, this, &MainWindow::buttonPushClearAll);

    // // Делеем свое контекстное меню у таблицы
    // connect(ui->PointsTable1, &QTableView::customContextMenuRequested, this, &MainWindow::showTable1ContextMenu);
    // connect(ui->PointsTable2, &QTableView::customContextMenuRequested, this, &MainWindow::showTable2ContextMenu);

    // connect(ui->SolveButton, &QPushButton::clicked, this, &MainWindow::buttonPushSolve);
    // connect(ui->NextButton, &QPushButton::clicked, this, &MainWindow::buttonPushNext);
    // connect(ui->ClearSolveButton, &QPushButton::clicked, this, &MainWindow::buttonPushclearSolve);
}

MainWindow::~MainWindow()
{
    delete ui;
}
