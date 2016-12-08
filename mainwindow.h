#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "event.h"
#include <QMainWindow>
#include <QDate>
#include <QVector>
#include <QTime>
#include <QTimer>



namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void AddTask();
    void CustomTask(QString nameTask, QColor colorTask);
    void FillCalendar();
    void FillListUnderCalendar(Event *task, QColor color);
    void FillTaskTable();
    void ReadFromFile (QString openFileName);
    void SaveToFile (QString saveFileName);
    void DeleteTask (QString nameTask, QColor colorTask);
    void DeleteAllTasks ();

    QTimer *mainTimer;

private slots:
    void on_pushButtonAddTask_Main_clicked();

    void on_pushButtonAddTask_OnWidget_clicked();

    void on_pushButtonToday_clicked();

    void on_tableWidgetMainTable_itemChanged();

    void on_pushButtonAddTask_OnTable_clicked();

    void on_calendarWidget_activated();

    void on_pushButtonCustomTask_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_calendarWidget_selectionChanged();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_pushButtonDeleteTask_clicked();

    void on_actionExit_triggered();

    void on_actionClose_triggered();

public slots:
    void mainTimer_overflow();

private:
    Ui::MainWindow *ui;

    bool doubleClickChk = false;
    QVector <Event*> eventsByPointer;

    QString fileName = "";
};

#endif // MAINWINDOW_H
