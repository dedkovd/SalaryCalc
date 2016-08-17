#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "employeesmodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new EmployeesModel();
    ui->treeView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    model->setModelDate(date);
}
