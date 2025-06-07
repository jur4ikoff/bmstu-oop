//lab_3

#include "mainwindow.hpp"

int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    app.setStyle("Fusion");

    MyMainWindow window;
    window.show();

    return app.exec();
}
