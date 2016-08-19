#include "addemployeedialog.h"
#include "ui_addemployeedialog.h"

#include "employee.h"
#include "manager.h"
#include "sales.h"

AddEmployeeDialog::AddEmployeeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddEmployeeDialog)
{
    ui->setupUi(this);
}

AddEmployeeDialog::~AddEmployeeDialog()
{
    delete ui;
}

AbstractEmployee *AddEmployeeDialog::newEmployee() const
{
    AbstractEmployee *newEmployee;

    QString name = ui->leName->text();
    int baseSalary = ui->sbBaseSalary->value();
    QDate dateOfEmployed = ui->deDateOfEmployed->date();

    switch (ui->cbType->currentIndex()) {
    case 0:
       newEmployee = new Employee(-1, name, dateOfEmployed, baseSalary);
       break;
    case 1:
       newEmployee = new Manager(-1, name, dateOfEmployed, baseSalary);
       break;
    case 2:
       newEmployee = new Sales(-1, name, dateOfEmployed, baseSalary);
       break;
    default:
        break;
    }

    return newEmployee;
}

int AddEmployeeDialog::employeeType() const
{
    return ui->cbType->currentIndex();
}
