#ifndef MAINWINDOW_H__
#define MAINWINDOW_H__

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
    ~MainWindow();

private:
    Ui::MainWindow *ui; // Указатель на сгенерированный интерфейс
};

#endif // MAINWINDOW_H__
