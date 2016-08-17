#include "baseemployee.h"

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
    return this->_dateOfEmployment.daysTo(date) / 365;
}

AbstractEmployee *BaseEmployee::chief() const
{
    return _chief;
}
