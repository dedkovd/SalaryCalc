#ifndef EMPLOYEESMODEL_H
#define EMPLOYEESMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QModelIndex>

#include "abstractemployee.h"

class EmployeesModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit EmployeesModel();

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QDate modelDate() const;
    void setModelDate(const QDate &modelDate);

    bool setData(const QModelIndex &index, const QVariant &value, int role);
    bool removeRow(int row, const QModelIndex &parent);
    bool insertRow(int row, const QModelIndex &parent, AbstractEmployee *employee);

    Qt::ItemFlags flags(const QModelIndex &index) const;

    float totalSalary() const;

private:
    AbstractEmployee *rootEmployee;

    QDate _modelDate;

    void initFromDb();
};

#endif // EMPLOYEESMODEL_H
