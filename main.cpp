#include "MainWindow.h"
#include <QApplication>
#include <windows.h>

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    MainWindow w;
    w.show();
    return a.exec();
}
