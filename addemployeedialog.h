#ifndef ADDEMPLOYEEDIALOG_H
#define ADDEMPLOYEEDIALOG_H

#include <QDialog>
#include "baseemployee.h"

namespace Ui {
class AddEmployeeDialog;
}

class AddEmployeeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddEmployeeDialog(QWidget *parent = 0);
    ~AddEmployeeDialog();

    void setChief(BaseEmployee *chief);

    AbstractEmployee *newEmployee() const;
    int employeeType() const;

private:
    Ui::AddEmployeeDialog *ui;

    BaseEmployee *_chief;
};

#endif // ADDEMPLOYEEDIALOG_H
