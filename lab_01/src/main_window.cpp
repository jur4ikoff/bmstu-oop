#include "main_window.h"
#include "constants.hpp"
#include "errors.hpp"
#include "request.hpp"
#include "ui_main_window.h"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMenu>
#include <QMenuBar>

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

void MainWindow::open_file(void)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "", tr("Текстовые файлы (*.txt);;Все файлы (*)"));

    if (!filename.isEmpty())
    {
        QFile file(filename);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            request_t request = {.task = REQ_LOAD}; // Сюда дописать
            request_handler(request);
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
    request_t request = { .task = REQ_QUIT };
    request_handler(request);
    delete ui;
}
