#include "employeesfactory.h"

AbstractEmployee *EmployeesFactory::createEmployee(EmployeeKind kind, int id, QString name, QDate dateOfEmployment, int baseSalary, AbstractEmployee *chief)
{
    switch (kind) {
    case KindEmployee:
       return new Employee(id, name, dateOfEmployment, baseSalary, chief);
    case KindManager:
        return new Manager(id, name, dateOfEmployment, baseSalary, chief);
    case KindSales:
        return new Sales(id, name, dateOfEmployment, baseSalary, chief);
    default:
        break;
    }

    return NULL;
}
