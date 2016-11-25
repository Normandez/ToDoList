#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "event.h"
#include <QMainWindow>
#include <QDate>



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
    void CustomTask();
    void FillCalendar(Event *task, QColor color);
    void FillListUnderCalendar(Event *task, QColor color);
    void FillTaskTable(Event *task, QColor color);

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
};

#endif // MAINWINDOW_H
