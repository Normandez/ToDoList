#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "event.h"
#include <QMainWindow>
#include <QDate>
#include <QVector>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QTextCharFormat>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QXmlStreamAttribute>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QCloseEvent>



namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow       //Класс формы главного окна программы
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    bool doubleClickChk = false;        //Проверка двойного клика
    bool savedStatusChk = true;     //Проверка несохраненных изменений
    QVector <Event*> eventsByPointer;       //Вектор задач

    QString fileName = "";      //Имя файла для автоматического сохранения

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void AddTask();     //Добавить задачу
    void CustomTask(QString nameTask, QColor colorTask);        //Изменить задачу
    void FillCalendar();                                    //Заполнить календарь
    void FillListUnderCalendar(Event *task, QColor color);      //Заполнить список под календарем
    void FillTaskTable();                                   //Заполнить таблицу задач
    void ReadFromFile (QString openFileName);             //Считать данные из файла
    void SaveToFile (QString saveFileName);             //Записать данные в файл
    void DeleteTask (QString nameTask, QColor colorTask);       //Удалить задачу
    void DeleteAllTasks ();                             //Удалить все задачи
    void SelectCurrentTask (QString *nameTask, QColor *colorTask);      //Выбрать конекретную задачу

    QTimer *mainTimer;                          //Таймер напоминания

protected:
    virtual void closeEvent(QCloseEvent *e);        //Событие закрытия программы

private slots:
    void on_pushButtonAddTask_OnWidget_clicked();

    void on_tableWidgetMainTable_itemChanged();

    void on_pushButtonAddTask_OnTable_clicked();

    void on_calendarWidget_activated();

    void on_calendarWidget_clicked(const QDate &date);

    void on_calendarWidget_selectionChanged();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionExit_triggered();

    void on_actionClose_triggered();

    void on_listWidgetTasksForDay_itemSelectionChanged();

    void on_tableWidgetMainTable_itemSelectionChanged();

    void on_tabWidgetMain_currentChanged(int index);

    void on_actionToday_triggered();

    void on_actionAddTask_triggered();

    void on_actionCustomTask_triggered();

    void on_actionDeleteTask_triggered();

    void on_actionAbout_triggered();

public slots:
    void mainTimer_overflow();

};

#endif // MAINWINDOW_H
