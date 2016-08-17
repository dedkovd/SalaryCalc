#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "baseemployee.h"

class Employee : public BaseEmployee
{
public:
    explicit Employee(QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee *chief = 0);

    float salaryAtDate(const QDate date) const;
    float childsSalaryAtDate(QDate) const { return 0.f; }

    QList<AbstractEmployee*> allChildsTree() const { return QList<AbstractEmployee*>(); }
    QList<AbstractEmployee*> subordinates() const { return QList<AbstractEmployee*>(); }
};

#endif // EMPLOYEE_H
