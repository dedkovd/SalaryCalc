#ifndef DAL_H
#define DAL_H

#include <QVariant>

#include "abstractemployee.h"

class DAL
{
public:
    static bool init(QString baseName = ":memory:");

    static QList<AbstractEmployee *> getEmployeesFromBase();
    static void addEmployeeToBase(AbstractEmployee *employee);
    static void removeEmployeeFromBase(int id);
    static void updateEmployeeField(int fieldId, QVariant value, int employeeId);
};

#endif // DAL_H
