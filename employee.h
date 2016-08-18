#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "baseemployee.h"

class Employee : public BaseEmployee
{
public:
    explicit Employee(int id, QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee *chief = 0);

    float childsSalaryAtDate(QDate) const { return 0.f; }

    QList<AbstractEmployee*> allChildsTree() const { return QList<AbstractEmployee*>(); }
    QList<AbstractEmployee*> subordinates() const { return QList<AbstractEmployee*>(); }

protected:
    float calcSalaryAtDate(const QDate date) const;
};

#endif // EMPLOYEE_H
