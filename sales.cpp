#include "sales.h"

Sales::Sales(QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee *chief):
    Manager(name, dateOfEmployment, baseSalary, chief)
{
}

float Sales::salaryAtDate(QDate date)
{
    return this->baseSalary() +
            this->baseSalary() * (0.01 * qMin(35, this->yearsInCompanyAtDate(date))) +
            this->allLevelsSalaryAtDate(date) * 0.003;
}

float Sales::allLevelsSalaryAtDate(QDate date)
{
    float res = 0;

    foreach (AbstractEmployee *subordinator, this->allChildsTree()) {
        res += subordinator->salaryAtDate(date);
    }

    return res;
}
