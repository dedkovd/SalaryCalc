#include "employee.h"

Employee::Employee(int id, QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee* chief):
    BaseEmployee(id, name, dateOfEmployment, baseSalary, chief)
{}

float Employee::calcSalaryAtDate(QDate date) const
{
    return this->baseSalary() + this->baseSalary() * (0.03 * qMin(10, this->yearsInCompanyAtDate(date)));
}
