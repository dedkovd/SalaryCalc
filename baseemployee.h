#ifndef ABSTRACTEMPLOYEE_H
#define ABSTRACTEMPLOYEE_H

#include <QString>
#include <QDate>

class BaseEmployee
{
public:
    explicit BaseEmployee(QString name, QDate dateOfEmployment, int baseSalary, BaseEmployee *chief = 0);
    ~BaseEmployee();

    // Getters and setters
    QString name();
    void setName(QString value);

    QDate dateOfEmployment();
    void setDateOfEmployment(QDate value);

    int baseSalary();
    void setBaseSalary(int value);

    int yearsInCompanyAtDate(QDate date);

    virtual int salaryAtDate(QDate date) = 0;

private:
    QString _name;
    QDate _dateOfEmployment;
    int _baseSalary; // Используем int, чтобы не было погрешности при вычислениях, т.о. оклад харнится в условных копейках
    BaseEmployee *_chief;
};

#endif // ABSTRACTEMPLOYEE_H
