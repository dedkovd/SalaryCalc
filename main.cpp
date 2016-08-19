#include "mainwindow.h"
#include <QApplication>

#include "dal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool databaseWasInit = false;
    if (argc < 2)
    {
        databaseWasInit = DAL::init();
    }
    else
    {
        databaseWasInit = DAL::init(argv[1]);
    }

    if (!databaseWasInit)
    {
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
