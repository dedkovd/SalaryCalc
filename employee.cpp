#include "employee.h"

Employee::Employee(QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee* chief):
    BaseEmployee(name, dateOfEmployment, baseSalary, chief)
{}

float Employee::salaryAtDate(QDate date) const
{
    int yic = this->yearsInCompanyAtDate(date);

    if (yic < 0) // Если еще не работал, зарплата не положена
    {
        return 0;
    }

    return this->baseSalary() + this->baseSalary() * (0.03 * qMin(10, yic));
}
