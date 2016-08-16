#include "baseemployee.h"

BaseEmployee::BaseEmployee(QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee *chief)
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

QString BaseEmployee::name()
{
    return this->_name;
}

void BaseEmployee::setName(QString value)
{
    this->_name = value;
}

QDate BaseEmployee::dateOfEmployment()
{
    return this->_dateOfEmployment;
}

void BaseEmployee::setDateOfEmployment(QDate value)
{
    this->_dateOfEmployment = value;
}

int BaseEmployee::baseSalary()
{
    return this->_baseSalary;
}

void BaseEmployee::setBaseSalary(int value)
{
    this->_baseSalary = value;
}

int BaseEmployee::yearsInCompanyAtDate(QDate date)
{
    return this->_dateOfEmployment.daysTo(date) / 365;
}
