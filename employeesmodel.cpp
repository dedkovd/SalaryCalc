#include "employeesmodel.h"
#include "manager.h"
#include "sales.h"
#include "employee.h"

EmployeesModel::EmployeesModel()
{
    rootEmployee = new Manager("Invisible manager", QDate(1900,1,1),0);

    Sales *sales1 = new Sales(QString("Sales1"),QDate(2005,4,11),150,rootEmployee);
    Manager *manager1 = new Manager(QString("Manager1"), QDate(2006,1,13),200, sales1);
    Employee *empl1 = new Employee(QString("Employee1"), QDate(2007,8,10),100, manager1);
    Employee *empl2 = new Employee(QString("Employee2"), QDate(2005,11,11),110, manager1);
    Sales *sales2 = new Sales(QString("Sales2"),QDate(2007,1,25),120,manager1);
    Employee *empl3 = new Employee(QString("Employee3"), QDate(2005,4,11),80, sales2);
    Employee *empl4 = new Employee(QString("Employee4"),QDate(2006,1,13),105,sales1);
    Sales *sales3 = new Sales(QString("Sales3"),QDate(2007,8,10),115,sales1);
    Employee *empl5 = new Employee(QString("Employee5"),QDate(2005,11,11),100,sales3);
    Employee *empl6 = new Employee(QString("Employee6"),QDate(2007,1,25),120,sales3);

    ((Manager*)rootEmployee)->addSubordinate(sales1);

    sales1->addSubordinate(manager1);
    sales1->addSubordinate(empl4);
    sales1->addSubordinate(sales3);

    manager1->addSubordinate(empl1);
    manager1->addSubordinate(empl2);
    manager1->addSubordinate(sales2);

    sales2->addSubordinate(empl3);

    sales3->addSubordinate(empl5);
    sales3->addSubordinate(empl6);
}

QVariant EmployeesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    BaseEmployee *employee = static_cast<BaseEmployee*>(index.internalPointer());

    switch (index.column()) {
    case 0:
        return employee->name();
    case 1:
        return employee->dateOfEmployment();
    case 2:
        return employee->baseSalary();
    case 3:
        return employee->salaryAtDate(this->_modelDate);
    default:
        return QVariant();
    }
}

QModelIndex EmployeesModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
    {
        return QModelIndex();
    }

    AbstractEmployee *parentEmployee;

    if (!parent.isValid())
    {
        parentEmployee = rootEmployee;
    }
    else
    {
        parentEmployee = static_cast<BaseEmployee*>(parent.internalPointer());
    }

    BaseEmployee *subordinate = static_cast<BaseEmployee*>(parentEmployee->subordinates().at(row));
    if (subordinate)
    {
        return createIndex(row, column, subordinate);
    }
    else
    {
        return QModelIndex();
    }
}

QModelIndex EmployeesModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
    {
        return QModelIndex();
    }

    BaseEmployee *subordinate = static_cast<BaseEmployee*>(child.internalPointer());
    BaseEmployee *chief = static_cast<BaseEmployee*>(subordinate->chief());

    if (chief == rootEmployee)
    {
        return QModelIndex();
    }

    return createIndex(chief->chief()->subordinates().indexOf(chief),0,chief);
}

int EmployeesModel::rowCount(const QModelIndex &parent) const
{
    BaseEmployee *chief;
    if (parent.column() > 0)
    {
        return 0;
    }

    if (!parent.isValid())
    {
        chief = rootEmployee;
    }
    else
    {
        chief = static_cast<BaseEmployee*>(parent.internalPointer());
    }

    return chief->subordinates().count();
}

int EmployeesModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return 4;
}

QDate EmployeesModel::modelDate() const
{
    return _modelDate;
}

void EmployeesModel::setModelDate(const QDate &modelDate)
{
    _modelDate = modelDate;
    this->dataChanged(this->index(0,3,QModelIndex()), this->index(this->rowCount(QModelIndex()),3,QModelIndex()));
}

