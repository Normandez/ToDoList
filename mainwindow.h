#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>



namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString nameOfTask;
    QString descriptionOfTask;
    QDate startDate;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void AddTask();

private slots:
    void on_pushButtonAddTask_Main_clicked();

    void on_pushButtonAddTask_OnWidget_clicked();

    void on_pushButtonToday_clicked();

    void on_tableWidgetMainTable_itemChanged();

    void on_pushButtonAddTask_OnTable_clicked();

    void on_calendarWidget_activated(const QDate &date);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
