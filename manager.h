#ifndef MANAGER_H
#define MANAGER_H

#include "baseemployee.h"

class Manager : public BaseEmployee
{
public:
    explicit Manager(QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee* chief = 0);
    ~Manager();

    void addSubordinate(AbstractEmployee* employee);

    float childsSalaryAtDate(QDate date) const;

    QList<AbstractEmployee *> allChildsTree() const;
    QList<AbstractEmployee *> subordinates() const;

protected:
    float calcSalaryAtDate(const QDate date) const;

    QList<AbstractEmployee *> _subordinates;
};

#endif // MANAGER_H
