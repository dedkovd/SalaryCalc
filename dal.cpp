#include "dal.h"

#include <QtSql>
#include <QDebug>

#include "employeesfactory.h"

#define EMPLOYEES_QUERY "select id, parent, name, base_salary, date_of_employment, kind from employees order by parent"
#define EMPLOYEE_REMOVE_QUERY "delete from employees where id = :id"
#define EMPLOYEE_ADD_QUERY "insert into employees(parent, name, base_salary, date_of_employment, kind) values (:p, :n, :s, :d, :k)"
#define EMPLOYEE_UPDATE_QUERY "update employees set %1 = :val where id = :id"
#define INSERTED_ROW_ID_QUERY "select last_insert_rowid()"

bool DAL::init(QString baseName)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(baseName);

    if (!db.open())
    {
        qDebug() << db.lastError();
        return false;
    }

    QSqlQuery q;
    q.exec("PRAGMA foreign_keys = ON;"); // Включаем внешние ключи на уровне базы

    // Проверим наличие нужных таблиц
    bool tablesExists = false;
    if (q.exec("select count(*) from sqlite_master where name = 'employees'"))
    {
        q.first();
        tablesExists = q.value(0).toInt() == 1;
    }

    // Если таблиц нет - создадим их и наполним тестовыми значениями
    if (!tablesExists)
    {
        QFile f(":/db_init.sql");
        f.open(QFile::ReadOnly);
        QString script = f.readLine();
        while (!script.isEmpty())
        {
            QSqlQuery q;
            if (!q.exec(script))
            {
                qDebug() << q.lastError();
                return false;
            }
            script = f.readLine();
        }
        f.close();
    }

    return true;
}

// Будем предполагать что персонал не мигрирует между подчиненными
// При необходимости такой миграции DAL нужно переписывать на полноценный НСИ,
// который будет учитывать версионность элементов
QList<AbstractEmployee *> DAL::getEmployeesFromBase()
{
    QList<AbstractEmployee *> res;
    QHash<int, AbstractEmployee *> allEmployees;

    QSqlQuery q(EMPLOYEES_QUERY);
    q.first();
    do
    {
        int id = q.value("id").toInt();
        int kind = q.value("kind").toInt();
        int chiefId = q.value("parent").toInt();
        Manager *chief = (Manager*)allEmployees[chiefId];

        QString name = q.value("name").toString();
        QDate dateOfEmployment = q.value("date_of_employment").toDate();
        float baseSalary = q.value("base_salary").toFloat();

        AbstractEmployee *employee = EmployeesFactory::createEmployee((EmployeeKind)kind, id, name, dateOfEmployment, baseSalary);

        if (chief)
        {
            chief->addSubordinate(employee);
        }
        else
        {
            res.append(employee);
        }

        allEmployees[id] = employee;
    }
    while (q.next());

    return res;
}

void DAL::addEmployeeToBase(AbstractEmployee *employee)
{
    QSqlQuery q;
    q.prepare(EMPLOYEE_ADD_QUERY);
    q.bindValue(":p",(employee->chief())->id());
    q.bindValue(":n",employee->name());
    q.bindValue(":s",employee->baseSalary());
    q.bindValue(":d",employee->dateOfEmployment());
    q.bindValue(":k",employee->kind());

    if (q.exec())
    {
        q.exec(INSERTED_ROW_ID_QUERY);
        q.first();
        employee->setId(q.value(0).toInt());
    }
}

void DAL::removeEmployeeFromBase(int id)
{
    QSqlQuery q;
    q.prepare(EMPLOYEE_REMOVE_QUERY); // Все подчиненные автоматом удалятся на стороне базы
    q.bindValue(":id", id);
    q.exec();
}

void DAL::updateEmployeeField(int fieldId, QVariant value, int employeeId)
{
    QSqlQuery q;

    switch (fieldId) {
    case 0:
        q.prepare(QString(EMPLOYEE_UPDATE_QUERY).arg("name"));
        break;
    case 1:
        q.prepare(QString(EMPLOYEE_UPDATE_QUERY).arg("date_of_employment"));
        break;
    case 2:
        q.prepare(QString(EMPLOYEE_UPDATE_QUERY).arg("base_salary"));
        break;
    default:
        break;
    }

    q.bindValue(":val", value);
    q.bindValue(":id", employeeId);
    q.exec();
}

