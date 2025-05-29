#pragma once

#include "constants.hpp"
#include "elevator_system.hpp"

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

public slots:
    void handleFloorUp(int floor);
    void handleFloorDown(int floor);

private:
    Ui::MainWindow *ui; // Указатель на сгенерированный интерфейс

    ElevatorSystem elevator_system;
};
