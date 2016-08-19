#include "mainwindow.h"
#include <QApplication>

#include <QDebug>
#include <QtSql>

bool initDatabase(QString fileName = ":memory:")
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);
    if (!db.open())
    {
        return false;
    }

    QSqlQuery q;
    q.exec("PRAGMA foreign_keys = ON;");

    bool tablesExists = false;
    if (q.exec("select count(*) from sqlite_master where name = 'employees'"))
    {
        q.first();
        tablesExists = q.value(0).toInt() == 1;
    }

    if (!tablesExists)
    {
        QFile f(":/db_init.sql");
        f.open(QFile::ReadOnly);
        QString script = f.readLine();
        while (!script.isEmpty())
        {
            QSqlQuery q;
            if (!q.exec(script))
            {
                qDebug() << q.lastError();
                return false;
            }
            script = f.readLine();
        }
        f.close();
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool databaseWasInit = false;
    if (argc < 2)
    {
        databaseWasInit = initDatabase();
    }
    else
    {
        databaseWasInit = initDatabase(argv[1]);
    }

    if (!databaseWasInit)
    {
        return -1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}
