#include "main_window.h"
#include "constants.hpp"
#include "errors.hpp"
#include "render.hpp"
#include "request.hpp"
#include "ui_main_window.h"
#include "utils.hpp"

#include <QAction>
#include <QDebug>
#include <QFileDialog>
#include <QInputDialog>
#include <QMenu>
#include <QMenuBar>
#include <QPixmap>
#include <QString>

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

    pixmap = QPixmap(ui->render_widget->width(), ui->render_widget->height());
    ui->render_widget->setPixmap(pixmap);

    // Ставим все плейсхолдеры
    set_placeholders();

    // QFrame *frame = ui->render_widget;
    // render_field.scene = ui->render_widget;
    // render_field.width =  ui->render_widget.width();
    //  render_field.height = ui->render_widget.height();
    // draw_on_frame(ui->render_widget);
    // draw_on_frame(render_field.scene);
}

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
        request_t request = { .task = REQ_LOAD, .filename = str_filename };
        err_t rc = request_handler(request);
        if (rc == ERR_OK)
        {
            rc = draw_update();
            if (rc != ERR_OK)
                error_handler(rc);
        }
        else
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

err_t MainWindow::draw_update(void)
{
    render_t to_render = { .plane = &pixmap, .width = pixmap.width(), .height = pixmap.height() };
    request_t request = { .task = REQ_RENDER, .render = to_render };
    err_t rc = request_handler(request);
    if (rc != ERR_OK)
    {
        error_handler(rc);
    }
    else
    {
        ui->render_widget->setPixmap(pixmap);
    }

    return rc;
}

void MainWindow::on_button_shift_clicked(void)
{
    err_t rc = ERR_OK;

    QString x_str = ui->shift_x->text();
    QString y_str = ui->shift_y->text();
    QString z_str = ui->shift_z->text();

    // Проверяем, можно ли преобразовать текст в double
    bool ok_x, ok_y, ok_z;
    double x = x_str.toDouble(&ok_x);
    double y = y_str.toDouble(&ok_y);
    double z = z_str.toDouble(&ok_z);

    shift_t shift = {.x = 0, .y = 0, .z = 0};
    bool is_record = false;
    if (ok_x)
    {
        shift.x = x;
        is_record = true;
    }
    if (ok_y)
    {
        shift.y = y;
        is_record = true;
    }
    if (ok_z)
    {
        shift.z = z;
        is_record = true;
    }

    

    if (is_record)
    {
        request_t request = { .task = REQ_SHIFT, .shift = shift };
        rc = request_handler(request);
        if (rc == ERR_OK)
        {
            draw_update();
        }
        else
            error_handler(rc);
    }
    else
    {
        rc = ERR_WRONG_INPUT_LABEL;
        error_handler(rc);
    }
}

void MainWindow::on_button_turn_clicked(void)
{
    qDebug() << "turn";
}

void MainWindow::on_button_scale_clicked(void)
{
    err_t rc = ERR_OK;

    QString x_str = ui->scale_x->text();
    QString y_str = ui->scale_y->text();
    QString z_str = ui->scale_z->text();

    // Проверяем, можно ли преобразовать текст в double
    bool ok_x, ok_y, ok_z;
    double x = x_str.toDouble(&ok_x);
    double y = y_str.toDouble(&ok_y);
    double z = z_str.toDouble(&ok_z);

    scale_t scale = {.x = 1, .y = 1, .z = 1};
    bool is_record = false;
    if (ok_x)
    {
        scale.x = x;
        is_record = true;
    }
    if (ok_y)
    {
        scale.y = y;
        is_record = true;
    }
    if (ok_z)
    {
        scale.z = z;
        is_record = true;
    }

    if (is_record)
    {
        request_t request = { .task = REQ_SCALE, .scale = scale };
        rc = request_handler(request);
        if (rc == ERR_OK)
        {
            draw_update();
        }
        else
            error_handler(rc);
    }
    else
    {
        rc = ERR_WRONG_INPUT_LABEL;
        error_handler(rc);
    }
}

MainWindow::~MainWindow(void)
{
    request_t request = { .task = REQ_QUIT };

    request_handler(request);
    delete ui;
}
