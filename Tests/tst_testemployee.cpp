#include <QString>
#include <QtTest>

#include "employee.h"

class TestEmployee : public QObject
{
    Q_OBJECT

public:
    TestEmployee() {}

private Q_SLOTS:
    void yearsInCompanyAtDate();
    void yearsInCompanyAtDate_data();

    void salaryAtDate();
    void salaryAtDate_data();
};

void TestEmployee::yearsInCompanyAtDate()
{
    Employee empl(QString(""), QDate(2005,4,11),0);

    QFETCH(QDate, date);
    QFETCH(int, years);

    QCOMPARE(empl.yearsInCompanyAtDate(date), years);
}

void TestEmployee::yearsInCompanyAtDate_data()
{
    QTest::addColumn<QDate>("date");
    QTest::addColumn<int>("years");

    QTest::newRow("31.12.2005") << QDate(2005,12,31) << 0;
    QTest::newRow("10.04.2006") << QDate(2006,4,10) << 0;
    QTest::newRow("31.12.2006") << QDate(2006,12,31) << 1;
    QTest::newRow("12.04.2007") << QDate(2007,4,12) << 2;
    QTest::newRow("31.05.2008") << QDate(2008,5,31) << 3;
}

void TestEmployee::salaryAtDate()
{
    Employee empl(QString(""), QDate(2005,4,11),100);

    QFETCH(QDate, date);
    QFETCH(int, result);

    QCOMPARE(empl.salaryAtDate(date), result);
}

void TestEmployee::salaryAtDate_data()
{
    QTest::addColumn<QDate>("date");
    QTest::addColumn<int>("result");

    QTest::newRow("first year 1") << QDate(2005,12,31) << 100;
    QTest::newRow("first year 2") << QDate(2006,4,10) << 100;
    QTest::newRow("2nd year") << QDate(2006,12,31) << 103;
    QTest::newRow("3th year") << QDate(2007,4,12) << 106;
    QTest::newRow("4th year") << QDate(2008,5,31) << 109;
    QTest::newRow("5th year") << QDate(2009,5,31) << 112;
    QTest::newRow("6th year") << QDate(2010,5,31) << 115;
    QTest::newRow("7th year") << QDate(2011,5,31) << 118;
    QTest::newRow("8th year") << QDate(2012,5,31) << 121;
    QTest::newRow("9th year") << QDate(2013,5,31) << 124;
    QTest::newRow("10th year") << QDate(2014,5,31) << 127;
    QTest::newRow("11th year") << QDate(2015,5,31) << 130;
    QTest::newRow("12th year") << QDate(2016,5,31) << 130;
    QTest::newRow("13th year") << QDate(2016,5,31) << 130;
}

QTEST_APPLESS_MAIN(TestEmployee)

#include "tst_testemployee.moc"
