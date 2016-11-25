#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "event.h"
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
    nameTableHeaders << "Название" << "Начало" << "Окончание" << "Кратность" << "Напоминание" << "Описание";
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
    Event *task = new Event();      //Создаем объект класса задачи

    AddNewTask *AddTaskWindow = new AddNewTask(this, ui->calendarWidget->selectedDate(), task);
    AddTaskWindow->exec();

    QColor color = QColor(rand()%255+1, rand()%255+1, rand()%255+1);        //Случайный выбор цвета

    FillCalendar(task, color);      //Заполнение календаря

    if (doubleClickChk) {FillListUnderCalendar(task, color); doubleClickChk = false;}     //Заполнения списка под календарем

    FillTaskTable(task, color);
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
    doubleClickChk = true;

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
void MainWindow::on_calendarWidget_activated()
{
    doubleClickChk = true;

    AddTask();
}
//



//Вункция изменения задачи
void MainWindow::CustomTask()
{

}
//



//Кнопка "Изменить задачу"
void MainWindow::on_pushButtonCustomTask_clicked()
{
    CustomTask();
}
//



//Функция заполнения календаря задачами
void MainWindow::FillCalendar(Event *task, QColor color)
{
    QTextCharFormat formatCalendar;
    formatCalendar.setBackground(color);

    QDate dateCount = task->GetStartDate();
    int day = dateCount.day();
    int month = dateCount.month();
    int year = dateCount.year();
    while (dateCount <= task->GetFinishDate())
    {
        ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
        day++;
        if (day > dateCount.daysInMonth()) {month++; day = 1;}
        if (month > 12) {year++; month = 1;}
        dateCount.setDate(year, month, day);
    }
}
//



//Функция заполнения списка задач под календарем
void MainWindow::FillListUnderCalendar(Event *task, QColor color)
{
    //Обработка видимости кнопок добавления задачи на полях отображения информации
    ui->pushButtonAddTask_OnWidget->setVisible(false);
    ui->pushButtonAddTask_OnTable->setVisible(false);
    ui->labelAdd_OnCalendar->setVisible(false);
    ui->labelAdd_OnTable->setVisible(false);
    //

    QListWidgetItem *item =new QListWidgetItem();

    item->setText("Задача: '" + task->GetNameOfTask() + "'\n\nОписание:\n" + task->GetDescriptionOfTask());
    item->setBackground(color);
    ui->listWidgetTasksForDay->addItem(item);
}
//



//Функция заполнения таблицы задач
void MainWindow::FillTaskTable(Event *task, QColor color)
{
    ui->tableWidgetMainTable->insertRow(ui->tableWidgetMainTable->rowCount());      //Вставка строки

    //Создание айтемов
    QTableWidgetItem *tableItemName = new QTableWidgetItem (task->GetNameOfTask());
    tableItemName->setTextColor(color);
    QTableWidgetItem *tableItemStartDate = new QTableWidgetItem (task->GetStartDate().toString("dd.MM.yyyy") + " в " + task->GetStartTime().toString("hh:mm"));
    QTableWidgetItem *tableItemFinishDate = new QTableWidgetItem (task->GetFinishDate().toString("dd.MM.yyyy") + " в " + task->GetFinishTime().toString("hh:mm"));
    QTableWidgetItem *tableItemDescription = new QTableWidgetItem (task->GetDescriptionOfTask());
    //

    //Установка айтемов
    ui->tableWidgetMainTable->setItem(ui->tableWidgetMainTable->rowCount() - 1, 0, tableItemName);
    ui->tableWidgetMainTable->setItem(ui->tableWidgetMainTable->rowCount() - 1, 1, tableItemStartDate);
    ui->tableWidgetMainTable->setItem(ui->tableWidgetMainTable->rowCount() - 1, 2, tableItemFinishDate);
    ui->tableWidgetMainTable->setItem(ui->tableWidgetMainTable->rowCount() - 1, 5, tableItemDescription);
    //
}
//



//Функция заполнения списка задач под календарем
void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QListWidgetItem *item =new QListWidgetItem();
    int Row = 0;
    QTextCharFormat formatCalendar = ui->calendarWidget->dateTextFormat(ui->calendarWidget->selectedDate());
    while (Row < ui->tableWidgetMainTable->rowCount())
    {
        if (formatCalendar.background().color() == ui->tableWidgetMainTable->item(Row, 0)->textColor())
        {
            //Избежание повторения задач под календарем
            for (short i = 0; i < ui->listWidgetTasksForDay->count(); i++)
            {
                if (ui->listWidgetTasksForDay->item(i)->backgroundColor() == formatCalendar.background().color()) return;
            }
            //

            //Обработка видимости кнопок добавления задачи на полях отображения информации
            ui->pushButtonAddTask_OnWidget->setVisible(false);
            ui->pushButtonAddTask_OnTable->setVisible(false);
            ui->labelAdd_OnCalendar->setVisible(false);
            ui->labelAdd_OnTable->setVisible(false);
            //

            //Добавление задачи под календарь
            item->setText("Задача: '" + ui->tableWidgetMainTable->item(Row, 0)->text() + "'\n\nОписание:\n" + ui->tableWidgetMainTable->item(Row, 5)->text());
            item->setBackground(ui->tableWidgetMainTable->item(Row, 0)->textColor());
            ui->listWidgetTasksForDay->addItem(item);
            //
            return;
        }
        else
        {
            //Обработка видимости кнопок добавления задачи на полях отображения информации
            ui->pushButtonAddTask_OnWidget->setVisible(true);
            ui->pushButtonAddTask_OnTable->setVisible(true);
            ui->labelAdd_OnCalendar->setVisible(true);
            ui->labelAdd_OnTable->setVisible(true);
            ui->listWidgetTasksForDay->clear();
            //
        }
        Row++;
    }
}
//



//Сброс списка задач под календарем во время смены даты
void MainWindow::on_calendarWidget_selectionChanged()
{
    ui->listWidgetTasksForDay->clear();
}
//
