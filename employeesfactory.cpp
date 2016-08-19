#include "employeesfactory.h"

AbstractEmployee *EmployeesFactory::createEmployee(EmployeeKind kind, int id, QString name, QDate dateOfEmployment, int baseSalary)
{
    switch (kind) {
    case KindEmployee:
       return new Employee(id, name, dateOfEmployment, baseSalary);
    case KindManager:
        return new Manager(id, name, dateOfEmployment, baseSalary);
    case KindSales:
        return new Sales(id, name, dateOfEmployment, baseSalary);
    default:
        break;
    }

    return NULL;
}
