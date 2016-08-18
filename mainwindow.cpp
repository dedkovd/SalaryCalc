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
    ui->treeView->header()->setStretchLastSection(false);
    ui->treeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
                          this, SLOT(refreshTotals()));

    ui->deCurrentDate->setDate(QDate::currentDate());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_deCurrentDate_dateChanged(const QDate &date)
{
    model->setModelDate(date);
}

void MainWindow::refreshTotals()
{
    ui->lblTotalSalaryValue->setText(QString("%1").arg(model->totalSalary()));
}
