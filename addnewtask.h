#ifndef ADDNEWTASK_H
#define ADDNEWTASK_H

<<<<<<< HEAD
#include "event.h"
=======
<<<<<<< HEAD
=======
#include "event.h"
>>>>>>> b126979570160e1560f69ca775275d0c5a803563
>>>>>>> ForMerging
#include <QDialog>



namespace Ui {
class AddNewTask;
}



class AddNewTask : public QDialog
{
    Q_OBJECT

public:
<<<<<<< HEAD
    explicit AddNewTask(QWidget *parent, QDate startDate, Event *objTask);
    explicit AddNewTask(QWidget *parent, Event *objTask);
=======
<<<<<<< HEAD
    explicit AddNewTask(QWidget *parent, QString *NewName, QDate *startDate, QString *Description);
=======
    explicit AddNewTask(QWidget *parent, QDate startDate, Event *objTask);
    explicit AddNewTask(QWidget *parent, Event *objTask);
>>>>>>> b126979570160e1560f69ca775275d0c5a803563
>>>>>>> ForMerging
    ~AddNewTask();

private slots:
    void on_checkBox_toggled(bool checked);

    void on_pushButtonCancel_clicked();

    void on_pushButtonOK_clicked();

    void on_dateEditFinishDate_dateChanged(const QDate &date);

    void on_dateTimeEditFinishTime_timeChanged(const QTime &time);

private:
    Ui::AddNewTask *ui;

<<<<<<< HEAD
    Event *obj;
    QDate sDate;
=======
<<<<<<< HEAD
    QString *Name;
    QString *descript;
    QDate *sDate;
=======
    Event *obj;
    QDate sDate;
>>>>>>> b126979570160e1560f69ca775275d0c5a803563
>>>>>>> ForMerging
};

#endif // ADDNEWTASK_H
