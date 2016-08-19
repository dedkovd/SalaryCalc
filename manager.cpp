#include "manager.h"

Manager::Manager(int id, QString name, QDate dateOfEmployment, int baseSalary):
    Employee(id,name,dateOfEmployment,baseSalary)
{
}

Manager::~Manager()
{
    this->_subordinates.clear();
}

void Manager::addSubordinate(AbstractEmployee *employee)
{
    this->_subordinates.append(employee);
    employee->setChief(this);
}

void Manager::removeSubordinate(const int index)
{
    this->_subordinates.removeAt(index);
}

int Manager::subordinateId(const int index)
{
    Employee *subordinate = (Employee*)this->_subordinates.at(index);
    return subordinate->id();
}

float Manager::calcSalaryAtDate(QDate date) const
{
    return this->baseSalary() +
            this->baseSalary() * (0.05 * qMin(8, this->yearsInCompanyAtDate(date))) +
            this->childsSalaryAtDate(date) * 0.005;
}

float Manager::childsSalaryAtDate(QDate date) const
{
    float res = 0;
    foreach(AbstractEmployee *subordinator, this->_subordinates)
    {
        res += subordinator->salaryAtDate(date);
    }

    return res;
}

QList<AbstractEmployee *> Manager::allSubordinates() const
{
    QList<AbstractEmployee*> res;

    foreach(AbstractEmployee *subordinator, this->_subordinates)
    {
        res.append(subordinator);
        foreach (AbstractEmployee *subsub, subordinator->allSubordinates())
        {
            res.append(subsub);
        }
    }

    return res;
}

QList<AbstractEmployee *> Manager::subordinates() const
{
    return this->_subordinates;
}
