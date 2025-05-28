#include "main_window.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    MainWindow window;
    window.show();
    
    return application.exec();
}
