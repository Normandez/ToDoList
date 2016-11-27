#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "event.h"
#include <QMainWindow>
#include <QDate>
#include <QVector>



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
    void CustomTask(QString nameTask);
    void FillCalendar();
    void FillListUnderCalendar(Event *task, QColor color);
    void FillTaskTable();

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

private:
    Ui::MainWindow *ui;

    bool doubleClickChk = false;
    QVector <Event*> eventsByPointer;
};

#endif // MAINWINDOW_H
