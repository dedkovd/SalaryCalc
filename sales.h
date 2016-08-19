#ifndef SALES_H
#define SALES_H

#include "manager.h"

class Sales : public Manager
{
public:
    Sales(int id, QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee* chief = 0);

    EmployeeKind kind() const { return KindSales; }

protected:
    float calcSalaryAtDate(const QDate date) const;
    float allLevelsSalaryAtDate(QDate date) const;
};

#endif // SALES_H
