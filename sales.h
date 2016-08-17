#ifndef SALES_H
#define SALES_H

#include "manager.h"

class Sales : public Manager
{
public:
    Sales(QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee* chief = 0);

    float salaryAtDate(QDate date);

private:
    float allLevelsSalaryAtDate(QDate date);
};

#endif // SALES_H
