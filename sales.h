#ifndef SALES_H
#define SALES_H

#include "manager.h"

class Sales : public Manager
{
public:
    Sales(QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee* chief = 0);

protected:
    float calcSalaryAtDate(const QDate date) const;
    float allLevelsSalaryAtDate(QDate date) const;
};

#endif // SALES_H
