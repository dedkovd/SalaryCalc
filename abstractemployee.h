#ifndef ABSTRACTEMPLOYEE
#define ABSTRACTEMPLOYEE

class AbstractEmployee
{
public:
    virtual ~AbstractEmployee() {}
    virtual float salaryAtDate(const QDate date) const = 0;
    virtual float childsSalaryAtDate(const QDate date) const = 0;
    virtual QList<AbstractEmployee*> allChildsTree() const = 0;
    virtual QList<AbstractEmployee*> subordinates() const = 0;

protected:
    virtual float calcSalaryAtDate(const QDate date) const = 0;
};

#endif // ABSTRACTEMPLOYEE

