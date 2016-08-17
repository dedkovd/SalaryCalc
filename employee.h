#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "baseemployee.h"

class Employee : public BaseEmployee
{
public:
    explicit Employee(QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee *chief = 0);

    float salaryAtDate(QDate date);
    float childsSalaryAtDate(QDate) { return 0.f; }

    QList<AbstractEmployee*> allChildsTree() { return QList<AbstractEmployee*>(); }
};

#endif // EMPLOYEE_H
