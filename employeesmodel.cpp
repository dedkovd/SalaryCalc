#include "employeesmodel.h"
#include "manager.h"
#include "dal.h"

#include <QIcon>

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

    if (role != Qt::DisplayRole && role != Qt::EditRole && role != Qt::DecorationRole)
    {
        return QVariant();
    }

    AbstractEmployee *employee = static_cast<AbstractEmployee*>(index.internalPointer());

    if (role == Qt::DecorationRole && index.column() == 0)
    {
        return QIcon(QString(":/images/%1").arg(employee->kind()));
    }

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
        parentEmployee = static_cast<AbstractEmployee*>(parent.internalPointer());
    }

    AbstractEmployee *subordinate = static_cast<AbstractEmployee*>(parentEmployee->subordinates().at(row));
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

    AbstractEmployee *subordinate = static_cast<AbstractEmployee*>(child.internalPointer());
    AbstractEmployee *chief = static_cast<AbstractEmployee*>(subordinate->chief());

    if (chief == rootEmployee)
    {
        return QModelIndex();
    }

    return createIndex(chief->chief()->subordinates().indexOf(chief),0,chief);
}

int EmployeesModel::rowCount(const QModelIndex &parent) const
{
    AbstractEmployee *chief;
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
        chief = static_cast<AbstractEmployee*>(parent.internalPointer());
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

    AbstractEmployee *employee = static_cast<AbstractEmployee*>(index.internalPointer());

    DAL::updateEmployeeField(index.column(), value, employee->id());

    switch (index.column()) {
    case 0:
        employee->setName(value.toString());
        break;
    case 1:
        employee->setDateOfEmployment(value.toDate());
        break;
    case 2:
        employee->setBaseSalary(value.toInt());
        break;
    default:
        return false;
    }

    emit dataChanged(index, index);

    return true;
}

bool EmployeesModel::removeRow(int row, const QModelIndex &parent)
{
    if (!parent.isValid())
    {
        return false;
    }

    Manager *manager = static_cast<Manager*>(parent.internalPointer());

    beginRemoveRows(parent, row, row+1);

    DAL::removeEmployeeFromBase(manager->subordinateId(row));

    manager->removeSubordinate(row);
    endRemoveRows();

    return true;
}

bool EmployeesModel::insertRow(int row, const QModelIndex &parent, AbstractEmployee *employee)
{
    if (!parent.isValid())
    {
        return false;
    }

    beginInsertRows(parent, row, row+1);

    ((Manager*)employee->chief())->addSubordinate(employee);
    DAL::addEmployeeToBase(employee);

    endInsertRows();

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
    QList<AbstractEmployee *> employees = DAL::getEmployeesFromBase();

    foreach (AbstractEmployee *employee, employees) {
        ((Manager*)rootEmployee)->addSubordinate(employee);
    }
}

float EmployeesModel::totalSalary() const
{
    QList<AbstractEmployee*> allEmployes = rootEmployee->allSubordinates();
    float res = 0.f;
    foreach (AbstractEmployee * empl, allEmployes)
    {
        res += empl->salaryAtDate(this->modelDate());
    }

    return res;
}

