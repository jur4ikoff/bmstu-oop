#ifndef MAINWINDOW_H__
#define MAINWINDOW_H__

#include "errors.hpp"
#include "render.hpp"

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
    void on_button_shift_clicked(void);
    void on_button_turn_clicked(void);
    void on_button_scale_clicked(void);

    void open_file(void);

private:
    QPixmap pixmap;
    err_t draw_update(void);
    void set_placeholders(void);
    Ui::MainWindow *ui; // Указатель на сгенерированный интерфейс
};

#endif // MAINWINDOW_H__
