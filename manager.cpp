#include "manager.h"

#include <QDebug>

Manager::Manager(QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee *chief):
    BaseEmployee(name,dateOfEmployment, baseSalary, chief)
{
}

Manager::~Manager()
{
    this->_subordinates.clear();
}

void Manager::addSubordinate(AbstractEmployee *employee)
{
    this->_subordinates.append(employee);
}

float Manager::salaryAtDate(QDate date) const
{
    int yic = this->yearsInCompanyAtDate(date);

    if (yic < 0) // Если еще не работал, зарплата не положена
    {
        return 0;
    }

    return this->baseSalary() +
            this->baseSalary() * (0.05 * qMin(8, yic)) +
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

QList<AbstractEmployee *> Manager::allChildsTree() const
{
    QList<AbstractEmployee*> res;

    foreach(AbstractEmployee *subordinator, this->_subordinates)
    {
        res.append(subordinator);
        foreach (AbstractEmployee *subsub, subordinator->allChildsTree())
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
