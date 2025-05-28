#pragma once

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

private slots:

private:
    Ui::MainWindow *ui; // Указатель на сгенерированный интерфейс
};
