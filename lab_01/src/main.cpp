#include "main_window.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    MainWindow window;
    window.show();
    
    return application.exec();
}
