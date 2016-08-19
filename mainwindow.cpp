#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "addemployeedialog.h"
#include "employeesmodel.h"
#include "manager.h"
#include "employee.h"

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

    connect(ui->treeView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(updateActions()));

    ui->deCurrentDate->setDate(QDate::currentDate());

    updateActions();
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

void MainWindow::on_actionRemove_employee_triggered()
{
    QModelIndex selected = ui->treeView->currentIndex();
    if (model->removeRow(selected.row(), selected.parent()))
    {
        updateActions();
    }
}

void MainWindow::updateActions()
{
    QModelIndex idx = ui->treeView->currentIndex();

    ui->actionAdd_employee->setEnabled(false);
    ui->actionRemove_employee->setEnabled(idx.isValid());
    if (idx.isValid())
    {
        AbstractEmployee *empl = static_cast<AbstractEmployee*>(idx.internalPointer());
        ui->actionAdd_employee->setEnabled(empl->canHaveSubbordinates());
    }
}

void MainWindow::on_actionAdd_employee_triggered()
{
    QModelIndex selected = ui->treeView->currentIndex();
    Manager *manager = static_cast<Manager*>(selected.internalPointer());

    AddEmployeeDialog d;
    d.setChief(manager);
    if (d.exec() == QDialog::Accepted)
    {
        model->insertRow(selected.row(), selected, d.employeeType(), (AbstractEmployee*)d.newEmployee());
    }
}
