#include <QString>
#include <QtTest>

#include "employee.h"
#include "manager.h"
#include "sales.h"

class TestEmployee : public QObject
{
    Q_OBJECT

public:
    TestEmployee() {}

private Q_SLOTS:
    void yearsInCompanyAtDate();
    void yearsInCompanyAtDate_data();

    void employeeSalaryAtDate();
    void employeeSalaryAtDate_data();

    void managerSalaryAtDate();
    void managerSalaryAtDate_data();

    void salesSalaryAtDate();
    void salesSalaryAtDate_data();
};

void TestEmployee::yearsInCompanyAtDate()
{
    Employee empl(0, QString(""), QDate(2005,4,11),0);

    QFETCH(QDate, date);
    QFETCH(int, years);

    QCOMPARE(empl.yearsInCompanyAtDate(date), years);
}

void TestEmployee::yearsInCompanyAtDate_data()
{
    QTest::addColumn<QDate>("date");
    QTest::addColumn<int>("years");

    QTest::newRow("31.12.2004") << QDate(2004,12,31) << -1;
    QTest::newRow("11.03.2004") << QDate(2004,3,11) << -2;
    QTest::newRow("31.12.2005") << QDate(2005,12,31) << 0;
    QTest::newRow("10.04.2006") << QDate(2006,4,10) << 0;
    QTest::newRow("31.12.2006") << QDate(2006,12,31) << 1;
    QTest::newRow("12.04.2007") << QDate(2007,4,12) << 2;
    QTest::newRow("31.05.2008") << QDate(2008,5,31) << 3;
}

void TestEmployee::employeeSalaryAtDate()
{
    Employee empl(0, QString(""), QDate(2005,4,11),100);

    QFETCH(QDate, date);
    QFETCH(float, result);

    QCOMPARE(empl.salaryAtDate(date), result);
}

void TestEmployee::employeeSalaryAtDate_data()
{
    QTest::addColumn<QDate>("date");
    QTest::addColumn<float>("result");

    QTest::newRow("first year 1") << QDate(2005,12,31) << 100.f;
    QTest::newRow("first year 2") << QDate(2006,4,10) << 100.f;
    QTest::newRow("2nd year") << QDate(2006,12,31) << 103.f;
    QTest::newRow("3th year") << QDate(2007,4,12) << 106.f;
    QTest::newRow("4th year") << QDate(2008,5,31) << 109.f;
    QTest::newRow("5th year") << QDate(2009,5,31) << 112.f;
    QTest::newRow("6th year") << QDate(2010,5,31) << 115.f;
    QTest::newRow("7th year") << QDate(2011,5,31) << 118.f;
    QTest::newRow("8th year") << QDate(2012,5,31) << 121.f;
    QTest::newRow("9th year") << QDate(2013,5,31) << 124.f;
    QTest::newRow("10th year") << QDate(2014,5,31) << 127.f;
    QTest::newRow("11th year") << QDate(2015,5,31) << 130.f;
    QTest::newRow("12th year") << QDate(2016,5,31) << 130.f;
    QTest::newRow("13th year") << QDate(2017,5,31) << 130.f;
}

void TestEmployee::managerSalaryAtDate()
{
    Manager manager1(0, QString("manager1"), QDate(2005,4,11),200);
    Employee empl1(1, QString("empl1"), QDate(2006,1,13),100);
    Employee empl2(2, QString("empl2"), QDate(2007,8,10),110);
    Manager manager2(3, QString("manager2"), QDate(2005,11,11),150);
    manager1.addSubordinate(&manager2);
    manager1.addSubordinate(&empl1);
    manager1.addSubordinate(&empl2);

    Employee empl3(4, QString("empl3"), QDate(2007,1,25),105);
    manager2.addSubordinate(&empl3);

    QFETCH(QDate, date);
    QFETCH(float, result);

    QCOMPARE(manager1.salaryAtDate(date), result);
}

void TestEmployee::managerSalaryAtDate_data()
{
    QTest::addColumn<QDate>("date");
    QTest::addColumn<float>("result");

    QTest::newRow("first year 1") << QDate(2005,12,31) << 200.75f;
    QTest::newRow("first year 2") << QDate(2006,4,10) << 201.250f;
    QTest::newRow("2nd year") << QDate(2006,12,31) << 211.288f;
    QTest::newRow("3th year") << QDate(2007,4,12) << 221.305f;
    QTest::newRow("4th year") << QDate(2008,5,31) << 231.908f;
    QTest::newRow("5th year") << QDate(2009,5,31) << 241.977f;
    QTest::newRow("6th year") << QDate(2010,5,31) << 252.046f;
    QTest::newRow("7th year") << QDate(2011,5,31) << 262.115f;
    QTest::newRow("8th year") << QDate(2012,5,31) << 272.184f;
    QTest::newRow("9th year") << QDate(2013,5,31) << 282.253f;
    QTest::newRow("10th year") << QDate(2014,5,31) << 282.322f;
    QTest::newRow("11th year") << QDate(2015,5,31) << 282.354f;
    QTest::newRow("12th year") << QDate(2016,5,31) << 282.385f;
    QTest::newRow("13th year") << QDate(2017,5,31) << 282.402f;
}

void TestEmployee::salesSalaryAtDate()
{
    Sales sales1(0, QString("Sales1"),QDate(2005,4,11),150);
    Manager manager1(1, QString("Manager1"), QDate(2006,1,13),200);
    Employee empl1(2, QString("Employee1"), QDate(2007,8,10),100);
    Employee empl2(3, QString("Employee2"), QDate(2005,11,11),110);
    Sales sales2(4, QString("Sales2"),QDate(2007,1,25),120);
    Employee empl3(5, QString("Employee3"), QDate(2005,4,11),80);
    Employee empl4(6, QString("Employee4"),QDate(2006,1,13),105);
    Sales sales3(7, QString("Sales3"),QDate(2007,8,10),115);
    Employee empl5(8, QString("Employee5"),QDate(2005,11,11),100);
    Employee empl6(9, QString("Employee6"),QDate(2007,1,25),120);

    sales1.addSubordinate(&manager1);
    sales1.addSubordinate(&empl4);
    sales1.addSubordinate(&sales3);

    manager1.addSubordinate(&empl1);
    manager1.addSubordinate(&empl2);
    manager1.addSubordinate(&sales2);

    sales2.addSubordinate(&empl3);

    sales3.addSubordinate(&empl5);
    sales3.addSubordinate(&empl6);

    QFETCH(QDate, date);
    QFETCH(float, result);

    QCOMPARE(sales1.salaryAtDate(date), result);
}

void TestEmployee::salesSalaryAtDate_data()
{
    QTest::addColumn<QDate>("date");
    QTest::addColumn<float>("result");

    QTest::newRow("first year 1") << QDate(2005,12,31) << 150.870f;
    QTest::newRow("first year 2") << QDate(2006,4,10) << 151.787f;
    QTest::newRow("2nd year") << QDate(2006,12,31) << 153.313f;
    QTest::newRow("3th year") << QDate(2007,4,12) << 155.582f;
    QTest::newRow("4th year") << QDate(2008,5,31) << 157.811f;
    QTest::newRow("5th year") << QDate(2009,5,31) << 159.403f;
    QTest::newRow("6th year") << QDate(2010,5,31) << 160.996f;
    QTest::newRow("7th year") << QDate(2011,5,31) << 162.588f;
    QTest::newRow("8th year") << QDate(2012,5,31) << 164.181f;
    QTest::newRow("9th year") << QDate(2013,5,31) << 165.774f;
    QTest::newRow("10th year") << QDate(2014,5,31) << 167.366f;
    QTest::newRow("11th year") << QDate(2015,5,31) << 168.929f;
    QTest::newRow("12th year") << QDate(2016,5,31) << 170.484f;
    QTest::newRow("13th year") << QDate(2017,5,31) << 172.011f;
}

QTEST_APPLESS_MAIN(TestEmployee)

#include "tst_testemployee.moc"
