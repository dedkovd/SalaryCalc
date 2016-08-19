#include "employee.h"
#include "math.h"

Employee::Employee(int id, QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee* chief)
{
    _id = id;
    _name = name;
    _dateOfEmployment = dateOfEmployment;
    _baseSalary = baseSalary;
    _chief = chief;
}

Employee::~Employee()
{
    this->_chief = NULL;
}

QString Employee::name() const
{
    return this->_name;
}

void Employee::setName(const QString name)
{
    this->_name = name;
}

QDate Employee::dateOfEmployment() const
{
    return this->_dateOfEmployment;
}

void Employee::setDateOfEmployment(const QDate dateOfEmployment)
{
    this->_dateOfEmployment = dateOfEmployment;
}

float Employee::baseSalary() const
{
    return this->_baseSalary;
}

void Employee::setBaseSalary(const float baseSalary)
{
    this->_baseSalary = baseSalary;
}

int Employee::yearsInCompanyAtDate(const QDate date) const
{
    return  floor(this->_dateOfEmployment.daysTo(date) / 365.);
}

float Employee::salaryAtDate(const QDate date) const
{
    int yic = this->yearsInCompanyAtDate(date);

    if (yic < 0) // Если еще не работал, зарплата не положена
    {
        return 0.f;
    }

    return calcSalaryAtDate(date);
}

AbstractEmployee *Employee::chief() const
{
    return _chief;
}

int Employee::id() const
{
    return _id;
}

void Employee::setId(const int id)
{
    this->_id = id;
}

float Employee::calcSalaryAtDate(QDate date) const
{
    return this->baseSalary() + this->baseSalary() * (0.03 * qMin(10, this->yearsInCompanyAtDate(date)));
}
