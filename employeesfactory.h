#ifndef EMPLOYEESFACTORY_H
#define EMPLOYEESFACTORY_H

#include "employee.h"
#include "sales.h"
#include "manager.h"

class EmployeesFactory
{
public:
    static AbstractEmployee *createEmployee(EmployeeKind kind, int id, QString name, QDate dateOfEmployment, int baseSalary);
};

#endif // EMPLOYEESFACTORY_H
