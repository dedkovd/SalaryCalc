#ifndef MANAGER_H
#define MANAGER_H

#include "employee.h"

class Manager : public Employee
{
public:
    explicit Manager(int id, QString name, QDate dateOfEmployment, int baseSalary);
    ~Manager();

    void addSubordinate(AbstractEmployee* employee);
    void removeSubordinate(const int index);
    int subordinateId(const int index);

    float childsSalaryAtDate(QDate date) const;

    QList<AbstractEmployee *> allSubordinates() const;
    QList<AbstractEmployee *> subordinates() const;

    bool canHaveSubbordinates() const { return true; }

    EmployeeKind kind() const { return KindManager; }

protected:
    float calcSalaryAtDate(const QDate date) const;

    QList<AbstractEmployee *> _subordinates;
};

#endif // MANAGER_H
