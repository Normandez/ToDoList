#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addnewtask.h"
#include <QMessageBox>
#include <QTextCharFormat>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Инициализация таблицы задач
    QStringList nameTableHeaders;
    nameTableHeaders << "Название" << "Время начала" << "Время окончания" << "Кратность" << "Напоминание" << "Описание";
    ui->tableWidgetMainTable->setHorizontalHeaderLabels(nameTableHeaders);
    ui->tableWidgetMainTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //
}
//



MainWindow::~MainWindow()
{
    delete ui;
}



//ВНИМАНИЕ!!! Комментированные куски кода не трогать!




//Функция открытия окна добавления новой задачи
void MainWindow::AddTask ()
{
    startDate = ui->calendarWidget->selectedDate();

    AddNewTask *AddTaskWindow = new AddNewTask(this, &nameOfTask, &startDate, &descriptionOfTask);
    AddTaskWindow->exec();

    ui->pushButtonAddTask_OnWidget->setVisible(false);
    ui->pushButtonAddTask_OnTable->setVisible(false);
    ui->labelAdd_OnCalendar->setVisible(false);
    ui->labelAdd_OnTable->setVisible(false);

    QColor color = QColor(rand()%255+1, rand()%255+1, rand()%255+1);
    QTextCharFormat formatCalendar;
    formatCalendar.setBackground(color);
    ui->calendarWidget->setDateTextFormat(startDate, formatCalendar);

    QListWidgetItem *item =new QListWidgetItem("Задача: '" + nameOfTask.toUpper() + "'\n\nОписание:\n" + descriptionOfTask);
    item->setBackground(color);

    ui->listWidgetTasksForDay->addItem(item);

    ui->tableWidgetMainTable->insertRow(ui->tableWidgetMainTable->rowCount());
    QTableWidgetItem *tableItemName = new QTableWidgetItem (nameOfTask);
    QTableWidgetItem *tableItemDescription = new QTableWidgetItem (descriptionOfTask);
    QTableWidgetItem *tableItemStartDate = new QTableWidgetItem (startDate.toString().replace(" ", "/"));
    ui->tableWidgetMainTable->setItem(ui->tableWidgetMainTable->rowCount() - 1, 0, tableItemName);
    ui->tableWidgetMainTable->setItem(ui->tableWidgetMainTable->rowCount() - 1, 1, tableItemStartDate);
    ui->tableWidgetMainTable->setItem(ui->tableWidgetMainTable->rowCount() - 1, 5, tableItemDescription);
}
//



//Кнопка "Добавить задачу"
void MainWindow::on_pushButtonAddTask_Main_clicked()
{
    AddTask();
}
//



//Кнопка "+" на календаре
void MainWindow::on_pushButtonAddTask_OnWidget_clicked()
{
    AddTask();
}
//



//Кнопка "+" на таблице
void MainWindow::on_pushButtonAddTask_OnTable_clicked()
{
    AddTask();
}
//



//Кнопка "Сегодня"
void MainWindow::on_pushButtonToday_clicked()
{
    QDate today = QDate::currentDate();;
    ui->calendarWidget->setSelectedDate(today);
    ui->calendarWidget->setFocus();
}
//



//Динамическое изменения размеров ячеек таблицы
void MainWindow::on_tableWidgetMainTable_itemChanged()
{
    ui->tableWidgetMainTable->resizeColumnsToContents();
}
//




//Двойной клик на календарь
void MainWindow::on_calendarWidget_activated(const QDate &date)
{
    AddTask();
}
//
