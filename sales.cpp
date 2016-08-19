#include "sales.h"

Sales::Sales(int id, QString name, QDate dateOfEmployment, int baseSalary):
    Manager(id, name, dateOfEmployment, baseSalary)
{
}

float Sales::calcSalaryAtDate(QDate date) const
{
    return this->baseSalary() +
            this->baseSalary() * (0.01 * qMin(35, this->yearsInCompanyAtDate(date))) +
            this->allLevelsSalaryAtDate(date) * 0.003;
}

float Sales::allLevelsSalaryAtDate(QDate date) const
{
    float res = 0;

    foreach (AbstractEmployee *subordinator, this->allSubordinates()) {
        res += subordinator->salaryAtDate(date);
    }

    return res;
}
