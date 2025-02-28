#include "main_window.h"
#include <QApplication>
#include <QStyleFactory>

void set_white_theme(QApplication &app)
{
    QPalette light_palette;
    light_palette.setColor(QPalette::Window, Qt::white);
    light_palette.setColor(QPalette::WindowText, Qt::black);
    light_palette.setColor(QPalette::Base, QColor(240, 240, 240));
    light_palette.setColor(QPalette::AlternateBase, Qt::white);
    light_palette.setColor(QPalette::ToolTipBase, Qt::white);
    light_palette.setColor(QPalette::ToolTipText, Qt::black);
    light_palette.setColor(QPalette::Text, Qt::black);
    light_palette.setColor(QPalette::Button, QColor(240, 240, 240));
    light_palette.setColor(QPalette::ButtonText, Qt::black);
    light_palette.setColor(QPalette::BrightText, Qt::red);
    light_palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    light_palette.setColor(QPalette::HighlightedText, Qt::white);

    app.setPalette(light_palette);
}

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setStyle(QStyleFactory::create("Fusion"));

    // Установка светлой палитры
    set_white_theme(application);

    MainWindow window;
    window.show();
    return application.exec();
}
