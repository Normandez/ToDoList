#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QString nameOfTask;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void AddTask();

private slots:
    void on_pushButtonAddTask_Main_clicked();

    void on_pushButtonAddTask_OnWidget_clicked();

    void on_pushButtonToday_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
