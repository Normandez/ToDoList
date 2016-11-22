#ifndef ADDNEWTASK_H
#define ADDNEWTASK_H

#include <QDialog>

namespace Ui {
class AddNewTask;
}

class AddNewTask : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewTask(QWidget *parent = 0);
    ~AddNewTask();

private slots:
    void on_checkBox_toggled(bool checked);

    void on_pushButtonCancel_clicked();

private:
    Ui::AddNewTask *ui;
};

#endif // ADDNEWTASK_H
