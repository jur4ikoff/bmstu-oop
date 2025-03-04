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

protected:
    void draw_on_frame(QPainter &painter);
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_button_shift_clicked(void);
    void on_button_turn_clicked(void);
    void on_button_scale_clicked(void);

    void open_file(void);

private:
    render_t render_field = { 0 };
    
    Ui::MainWindow *ui; // Указатель на сгенерированный интерфейс
};

#endif // MAINWINDOW_H__
