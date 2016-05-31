#include "mainwindow.h"
#include <QApplication>
#include "TargetObject.h"
#include "myserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    MyServer server;
    server.StartServer();

    w.show();
    return a.exec();
}

