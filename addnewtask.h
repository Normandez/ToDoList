#ifndef ADDNEWTASK_H
#define ADDNEWTASK_H

#include "event.h"
#include <QDialog>



namespace Ui {
class AddNewTask;
}



class AddNewTask : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewTask(QWidget *parent, QDate startDate, Event *objTask);
    ~AddNewTask();

private slots:
    void on_checkBox_toggled(bool checked);

    void on_pushButtonCancel_clicked();

    void on_pushButtonOK_clicked();

    void on_dateEditFinishDate_dateChanged(const QDate &date);

    void on_dateTimeEditFinishTime_timeChanged(const QTime &time);

private:
    Ui::AddNewTask *ui;

    Event *obj;
    QDate sDate;
};

#endif // ADDNEWTASK_H
