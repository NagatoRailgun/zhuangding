#include "component/mainwindow/mainwindow.h"

#ifdef _WIN32
#include <windows.h>
#endif
#include <QApplication>

int main(int argc, char *argv[])
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
