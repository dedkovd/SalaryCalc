#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "baseemployee.h"

class Employee : public BaseEmployee
{
public:
    explicit Employee(QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee* chief = 0);

    int salaryAtDate(QDate date);
};

#endif // EMPLOYEE_H
