#ifndef ABSTRACTEMPLOYEE_H
#define ABSTRACTEMPLOYEE_H

#include <QString>
#include <QDate>

#include "abstractemployee.h"

class BaseEmployee: public AbstractEmployee
{
public:
    explicit BaseEmployee(int id, QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee *chief = 0);
    ~BaseEmployee();

    // Getters and setters
    QString name() const;
    void setName(const QString value);

    QDate dateOfEmployment() const;
    void setDateOfEmployment(const QDate value);

    int baseSalary() const;
    void setBaseSalary(const int value);

    int yearsInCompanyAtDate(const QDate date) const;

    float salaryAtDate(const QDate date) const;

    AbstractEmployee *chief() const;

protected:
    int _id;
    QString _name;
    QDate _dateOfEmployment;
    int _baseSalary; // Используем int, чтобы не было погрешности при вычислениях, т.о. оклад харнится в условных копейках
    AbstractEmployee *_chief;
};

#endif // ABSTRACTEMPLOYEE_H
