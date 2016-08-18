#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employeesmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void refreshTotals();
    void on_deCurrentDate_dateChanged(const QDate &date);

private:
    Ui::MainWindow *ui;
    EmployeesModel *model;
};

#endif // MAINWINDOW_H
