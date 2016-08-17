#include "sales.h"

Sales::Sales(QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee *chief):
    Manager(name, dateOfEmployment, baseSalary, chief)
{
}

float Sales::salaryAtDate(QDate date) const
{
    int yic = this->yearsInCompanyAtDate(date);

    if (yic < 0) // Если еще не работал, зарплата не положена
    {
        return 0;
    }

    return this->baseSalary() +
            this->baseSalary() * (0.01 * qMin(35, yic)) +
            this->allLevelsSalaryAtDate(date) * 0.003;
}

float Sales::allLevelsSalaryAtDate(QDate date) const
{
    float res = 0;

    foreach (AbstractEmployee *subordinator, this->allChildsTree()) {
        res += subordinator->salaryAtDate(date);
    }

    return res;
}
