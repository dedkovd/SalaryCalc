#ifndef MANAGER_H
#define MANAGER_H

#include "baseemployee.h"

class Manager : public BaseEmployee
{
public:
    explicit Manager(QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee* chief = 0);
    ~Manager();

    void addSubordinate(AbstractEmployee* employee);

    float salaryAtDate(QDate date);
    float childsSalaryAtDate(QDate date);

    QList<AbstractEmployee *> allChildsTree();

protected:
    QList<AbstractEmployee *> _subordinates;
};

#endif // MANAGER_H
