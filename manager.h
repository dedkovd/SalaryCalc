#ifndef MANAGER_H
#define MANAGER_H

#include "baseemployee.h"

class Manager : public BaseEmployee
{
public:
    explicit Manager(int id, QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee* chief = 0);
    ~Manager();

    void addSubordinate(AbstractEmployee* employee);
    void removeSubordinate(const int index);
    int subordinateId(const int index);

    float childsSalaryAtDate(QDate date) const;

    QList<AbstractEmployee *> allChildsTree() const;
    QList<AbstractEmployee *> subordinates() const;

    bool canHaveSubbordinates() const { return true; }

protected:
    float calcSalaryAtDate(const QDate date) const;

    QList<AbstractEmployee *> _subordinates;
};

#endif // MANAGER_H
