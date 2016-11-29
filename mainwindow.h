#ifndef MAINWINDOW_H
#define MAINWINDOW_H

<<<<<<< HEAD
#include <QMainWindow>
#include <QDate>
=======
#include "event.h"
#include <QMainWindow>
#include <QDate>
#include <QVector>
>>>>>>> b126979570160e1560f69ca775275d0c5a803563



namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
<<<<<<< HEAD
    QString nameOfTask;
    QString descriptionOfTask;
    QDate startDate;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void AddTask();
=======
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void AddTask();
    void CustomTask(QString nameTask, QColor colorTask);
    void FillCalendar();
    void FillListUnderCalendar(Event *task, QColor color);
    void FillTaskTable();
    void ReadFromFile ();
    void SaveToFile ();
    void DeleteTask (QString nameTask, QColor colorTask);
>>>>>>> b126979570160e1560f69ca775275d0c5a803563

private slots:
    void on_pushButtonAddTask_Main_clicked();

    void on_pushButtonAddTask_OnWidget_clicked();

    void on_pushButtonToday_clicked();

    void on_tableWidgetMainTable_itemChanged();

    void on_pushButtonAddTask_OnTable_clicked();

<<<<<<< HEAD
    void on_calendarWidget_activated(const QDate &date);

private:
    Ui::MainWindow *ui;
=======
    void on_calendarWidget_activated();

    void on_pushButtonCustomTask_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_calendarWidget_selectionChanged();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_pushButtonDeleteTask_clicked();

private:
    Ui::MainWindow *ui;

    bool doubleClickChk = false;
    QVector <Event*> eventsByPointer;
>>>>>>> b126979570160e1560f69ca775275d0c5a803563
};

#endif // MAINWINDOW_H
