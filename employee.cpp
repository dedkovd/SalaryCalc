#include "employee.h"

Employee::Employee(QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee* chief):
    BaseEmployee(name, dateOfEmployment, baseSalary, chief)
{}

float Employee::calcSalaryAtDate(QDate date) const
{
    return this->baseSalary() + this->baseSalary() * (0.03 * qMin(10, this->yearsInCompanyAtDate(date)));
}
