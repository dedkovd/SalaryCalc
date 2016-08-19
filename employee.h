#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include "abstractemployee.h"

class Employee : public AbstractEmployee
{
public:
    explicit Employee(int id, QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee *chief = 0);
    ~Employee();

    int id() const;
    void setId(const int id);

    QString name() const;
    void setName(const QString name);

    QDate dateOfEmployment() const;
    void setDateOfEmployment(const QDate dateOfEmployment);
    int yearsInCompanyAtDate(const QDate date) const;

    float baseSalary() const;
    void setBaseSalary(const float baseSalary);
    float salaryAtDate(const QDate date) const;

    EmployeeKind kind() const { return KindEmployee; }

    AbstractEmployee* chief() const;

    bool canHaveSubbordinates() const { return false; }
    QList<AbstractEmployee*> subordinates() const { return QList<AbstractEmployee*>(); }
    QList<AbstractEmployee*> allSubordinates() const { return QList<AbstractEmployee*>(); }

protected:
    float calcSalaryAtDate(const QDate date) const;

private:
    int _id;
    QString _name;
    QDate _dateOfEmployment;
    float _baseSalary;
    AbstractEmployee *_chief;
};

#endif // EMPLOYEE_H
