#include "main_window.h"
#include "constants.hpp"
#include "errors.hpp"
#include "request.hpp"
#include "ui_main_window.h"
#include "utils.hpp"

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

    // Ставим все плейсхолдеры
    set_placeholders();
}

// инициализируем систему координат
// CoordSystem *coordinate_system = new CoordSystem(points_1, points_2, solve, solve_cur, ui->ChartWidget);
// coordinate_system->setGeometry(ui->ChartWidget->geometry());

// Ставим плейсхолдеры в текст

void MainWindow::set_placeholders(void)
{
    ui->shift_x->setPlaceholderText("Введите координату x");
    ui->shift_y->setPlaceholderText("Введите координату y");
    ui->shift_z->setPlaceholderText("Введите координату z");

    ui->turn_x->setPlaceholderText("Введите координату x");
    ui->turn_y->setPlaceholderText("Введите координату y");
    ui->turn_z->setPlaceholderText("Введите координату z");

    ui->scale_x->setPlaceholderText("Введите координату x");
    ui->scale_y->setPlaceholderText("Введите координату y");
    ui->scale_z->setPlaceholderText("Введите координату z");
}

void MainWindow::open_file(void)
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Открыть файл"), "./../data/", tr("Текстовые файлы (*.txt);;Все файлы (*)"));
    if (!filename.isEmpty())
    {
        // Сделаем структуру, для запроса загрузки
        const char *str_filename = convert_QString_to_char(filename);
        request_t request = {.task = REQ_LOAD, .filename = str_filename};
        err_t rc = request_handler(request);
        if (rc != ERR_OK)
        {
            // Ошибка, не удалось открыть файл
            error_handler(rc);
        }
    }
    else
    {
        // Пользователь не выбрал файл
        qDebug() << "No file";
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
    request_t request = {.task = REQ_QUIT};
    request_handler(request);
    delete ui;
}
