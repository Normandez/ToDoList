#ifndef ADDNEWTASK_H
#define ADDNEWTASK_H

#include "event.h"
#include <QDialog>
#include <QMessageBox>
#include <QDate>



namespace Ui {
class AddNewTask;
}



class AddNewTask : public QDialog       //Класс формы окна "Добавить/Изменить задачу"
{
    Q_OBJECT

private:
    Ui::AddNewTask *ui;

    Event *obj;     //Задача
    QDate sDate;        //Дата начала задачи
    bool *chkCancel;        //Проверка статуса отмены

public:
    explicit AddNewTask(QWidget *parent, QDate startDate, Event *objTask, bool *cancel);        //Конструктор для добавления задачи
    explicit AddNewTask(QWidget *parent, Event *objTask, bool *cancel);         //Конструктор для изменения задачи
    ~AddNewTask();

private slots:
    void on_checkBox_toggled(bool checked);

    void on_pushButtonCancel_clicked();

    void on_pushButtonOK_clicked();

    void on_dateEditFinishDate_dateChanged(const QDate &date);

    void on_dateTimeEditFinishTime_timeChanged(const QTime &time);

    void on_dateEditStartDate_dateChanged(const QDate &date);

    void on_lineEditName_textChanged(const QString &arg1);

};

#endif // ADDNEWTASK_H
