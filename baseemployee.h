#ifndef ABSTRACTEMPLOYEE_H
#define ABSTRACTEMPLOYEE_H

#include <QString>
#include <QDate>

#include "abstractemployee.h"

class BaseEmployee: public AbstractEmployee
{
public:
    explicit BaseEmployee(QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee *chief = 0);
    ~BaseEmployee();

    // Getters and setters
    QString name();
    void setName(QString value);

    QDate dateOfEmployment();
    void setDateOfEmployment(QDate value);

    int baseSalary();
    void setBaseSalary(int value);

    int yearsInCompanyAtDate(QDate date);

protected:
    QString _name;
    QDate _dateOfEmployment;
    int _baseSalary; // Используем int, чтобы не было погрешности при вычислениях, т.о. оклад харнится в условных копейках
    AbstractEmployee *_chief;
};

#endif // ABSTRACTEMPLOYEE_H
