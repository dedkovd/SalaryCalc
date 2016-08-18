#include "employeesmodel.h"
#include "manager.h"
#include "sales.h"
#include "employee.h"

#include <QDebug>
#include <QtSql>

#define EMPLOYEES_QUERY "select id, parent, name, base_salary, date_of_employment, type from employees order by parent"
#define EMPLOYEE_REMOVE_QUERY "delete from employees where id = :id"
#define EMPLOYEE_ADD_QUERY "insert into employees(parent, name, base_salary, date_of_employment, type) values (:p, :n, :s, :d, :t)"
#define EMPLOYEE_UPDATE_QUERY "update employees set %1 = :val where id = :id"

EmployeesModel::EmployeesModel()
{
    rootEmployee = new Manager(0,"Invisible manager", QDate(1900,1,1),0);
    initFromDb();
}

QVariant EmployeesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole)
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

QVariant EmployeesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section) {
        case 0:
            return tr("Name");
        case 1:
            return tr("Date of employment");
        case 2:
            return tr("Base salary");
        case 3:
            return tr("Current salary");
        default:
            break;
        }
    }

    return QVariant();
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

bool EmployeesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role)

    if (!index.isValid())
    {
        return false;
    }

    BaseEmployee *employee = static_cast<BaseEmployee*>(index.internalPointer());

    QSqlQuery q;

    switch (index.column()) {
    case 0:
        employee->setName(value.toString());
        q.prepare(QString(EMPLOYEE_UPDATE_QUERY).arg("name"));
        break;
    case 1:
        employee->setDateOfEmployment(value.toDate());
        q.prepare(QString(EMPLOYEE_UPDATE_QUERY).arg("date_of_employment"));
        break;
    case 2:
        employee->setBaseSalary(value.toInt());
        q.prepare(QString(EMPLOYEE_UPDATE_QUERY).arg("base_salary"));
        break;
    default:
        return false;
    }

    q.bindValue(":val", value);
    q.bindValue(":id", employee->id());
    q.exec();

    return true;
}

bool EmployeesModel::removeRow(int row, const QModelIndex &parent)
{
    if (!parent.isValid())
    {
        return false;
    }

    Manager *employee = static_cast<Manager*>(parent.internalPointer());

    beginRemoveRows(parent, row, row+1);

    QSqlQuery q;
    q.prepare(EMPLOYEE_REMOVE_QUERY); // Все подчиненные автоматом удалятся на стороне базы
    q.bindValue(":id", employee->subordinateId(row));
    q.exec();

    employee->removeSubordinate(row);
    endRemoveRows();

    return true;
}

Qt::ItemFlags EmployeesModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return 0;
    }

    if (index.column() > 2)
    {
        return 0;
    }

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

void EmployeesModel::initFromDb()
{
    QHash<int, AbstractEmployee *> allEmployees;

    QSqlQuery q(EMPLOYEES_QUERY);
    q.first();
    do
    {
        int id = q.value("id").toInt();
        int type = q.value("type").toInt();
        int chiefId = q.value("parent").toInt();
        BaseEmployee *chief = (BaseEmployee*)allEmployees[chiefId];

        if (!chief)
        {
            chief = rootEmployee;
        }

        QString name = q.value("name").toString();
        QDate dateOfEmployment = q.value("date_of_employment").toDate();
        int baseSalary = q.value("base_salary").toInt();

        AbstractEmployee *employee;

        switch (type) {
        case 0:
            employee = new Employee(id, name, dateOfEmployment, baseSalary, chief);
            break;
        case 1:
            employee = new Manager(id, name, dateOfEmployment, baseSalary, chief);
            break;
        case 2:
            employee = new Sales(id, name, dateOfEmployment, baseSalary, chief);
            break;
        default:
            break;
        }

        ((Manager*)chief)->addSubordinate(employee);
        allEmployees[id] = employee;
    }
    while (q.next());
}

float EmployeesModel::totalSalary() const
{
    QList<AbstractEmployee*> allEmployes = rootEmployee->allChildsTree();
    float res = 0.f;
    foreach (AbstractEmployee * empl, allEmployes)
    {
        res += empl->salaryAtDate(this->modelDate());
    }

    return res;
}

