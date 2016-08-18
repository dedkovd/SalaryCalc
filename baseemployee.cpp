#include "baseemployee.h"
#include "math.h"

BaseEmployee::BaseEmployee(QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee *chief)
{
    _name = name;
    _dateOfEmployment = dateOfEmployment;
    _baseSalary = baseSalary;
    _chief = chief;
}

BaseEmployee::~BaseEmployee()
{
    this->_chief = NULL;
}

QString BaseEmployee::name() const
{
    return this->_name;
}

void BaseEmployee::setName(const QString value)
{
    this->_name = value;
}

QDate BaseEmployee::dateOfEmployment() const
{
    return this->_dateOfEmployment;
}

void BaseEmployee::setDateOfEmployment(const QDate value)
{
    this->_dateOfEmployment = value;
}

int BaseEmployee::baseSalary() const
{
    return this->_baseSalary;
}

void BaseEmployee::setBaseSalary(const int value)
{
    this->_baseSalary = value;
}

int BaseEmployee::yearsInCompanyAtDate(const QDate date) const
{
    return  floor(this->_dateOfEmployment.daysTo(date) / 365.);
}

float BaseEmployee::salaryAtDate(const QDate date) const
{
    int yic = this->yearsInCompanyAtDate(date);

    if (yic < 0) // Если еще не работал, зарплата не положена
    {
        return 0.f;
    }

    return calcSalaryAtDate(date);
}

AbstractEmployee *BaseEmployee::chief() const
{
    return _chief;
}
