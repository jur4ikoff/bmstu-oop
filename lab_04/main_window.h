#pragma once

#include "constants.hpp"
#include "lift.hpp"
#include "config.h"

#include <QMainWindow>

// Включаем сгенерированный заголовочный файл
QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(void);

signals:
    void floor_buttons_change_color_signal(int, direction_t, bool);
    void cabin_buttons_change_color_signal(int, cabin_id_t, bool);

public slots:
    void change_floor_button_style_slot(int floor_n, direction_t direction, bool is_active);
    void change_cabin_button_style_slot(int floor_n, cabin_id_t cabin, bool is_active);

private:
    Ui::MainWindow *ui; // Указатель на сгенерированный интерфейс

    LiftSystem lift_system;
};
