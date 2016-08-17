#ifndef ABSTRACTEMPLOYEE
#define ABSTRACTEMPLOYEE

class AbstractEmployee
{
public:
    virtual ~AbstractEmployee() {}
    virtual float salaryAtDate(QDate date) = 0;
    virtual float childsSalaryAtDate(QDate date) = 0;
    virtual QList<AbstractEmployee*> allChildsTree() = 0;
};

#endif // ABSTRACTEMPLOYEE

