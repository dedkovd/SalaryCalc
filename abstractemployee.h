#ifndef ABSTRACTEMPLOYEE
#define ABSTRACTEMPLOYEE

#include <QString>
#include <QDate>

enum EmployeeKind {
    KindEmployee,
    KindManager,
    KindSales
};

class AbstractEmployee
{
public:
    virtual ~AbstractEmployee() {}

    // Сотрудник должен быть уникальным
    virtual int id() const = 0;
    virtual void setId(const int id) = 0;
    // Сотрудник характеризуется именем
    virtual QString name() const = 0;
    virtual void setName(const QString name) = 0;
    // датой поступления на работу
    virtual QDate dateOfEmployment() const = 0;
    virtual void setDateOfEmployment(const QDate dateOfEmployment) = 0;
    // а значит и количеством проработанных лет
    virtual int yearsInCompanyAtDate(const QDate date) const = 0;
    // базовой ставкой
    virtual float baseSalary() const = 0;
    virtual void setBaseSalary(const float baseSalary) = 0;
    // а значит заработной платой
    virtual float salaryAtDate(const QDate date) const = 0;
    // сотрудник может быть трех видов
    virtual EmployeeKind kind() const = 0;
    // у каждого сотрудника может быть начальник
    virtual AbstractEmployee* chief() const = 0;
    // почти у каждого сотрудника могут быть подчиненные
    virtual bool canHaveSubbordinates() const = 0;
    virtual QList<AbstractEmployee*> subordinates() const = 0;
    // а у них могут быть свои подчиненные, поэтому добавим метод для всех
    virtual QList<AbstractEmployee*> allSubordinates() const = 0;

protected:
    // для сотрудников надо будет расчитывать зарплату на определенную дату
    virtual float calcSalaryAtDate(const QDate date) const = 0;
};

#endif // ABSTRACTEMPLOYEE

