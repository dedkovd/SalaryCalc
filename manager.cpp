#include "manager.h"

Manager::Manager(int id, QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee *chief):
    BaseEmployee(id,name,dateOfEmployment,baseSalary,chief)
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
