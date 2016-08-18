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
    ui->dateEdit->setDate(QDate::currentDate());
    ui->treeView->header()->setStretchLastSection(false);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    model->setModelDate(date);
}
