#include "main_window.h"
#include "ui_main_window.h"
#include "constants.hpp"
#include "errors.hpp"

#include <QDebug>
#include <QInputDialog>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setFixedSize(WINDOWS_X, WINDOWS_Y);

    // Создаем меню
    QMenu *file_menu = menuBar()->addMenu(tr("Файл"));
    QAction *open_action = new QAction(tr("Загрузить из файла"), this);
    file_menu->addAction(open_action);

    // Подключаем сигнал к слоту
    connect(open_action, &QAction::triggered, this, &MainWindow::open_file);
}

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

void MainWindow::open_file(void)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Текстовые файлы (*.txt);;Все файлы (*)"));

    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "file_open" << filename;
        }
        else
        {
            // Ошибка, не удалось открыть файл
            err_t err_code = ERR_FILE_OPEN;
            error_handler(err_code);
        }
    }
    else
    {
        qDebug() << "Exit";
    }
}
void MainWindow::on_button_shift_clicked(void)
{
    qDebug() << "1";
}

void MainWindow::on_button_turn_clicked(void)
{
    qDebug() << "turn";
}

void MainWindow::on_button_scale_clicked(void)
{
    qDebug() << "scale";
}

MainWindow::~MainWindow(void)
{
    delete ui;
}
