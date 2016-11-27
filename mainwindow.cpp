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

    task->SetColor(QColor(rand()%255+1, rand()%255+1, rand()%255+1));       //Случайный выбор цвета

    eventsByPointer.push_back(task);

    FillCalendar();      //Заполнение календаря

    if (doubleClickChk) {FillListUnderCalendar(task, task->GetColor()); doubleClickChk = false;}     //Заполнения списка под календарем

    ui->tableWidgetMainTable->insertRow(ui->tableWidgetMainTable->rowCount());      //Вставка строки

    FillTaskTable();        //Заполнение таблицы
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



//Функция изменения задачи
void MainWindow::CustomTask(QString nameTask, QColor colorTask)
{
    for (int i = 0; i < eventsByPointer.count(); i++)
    {
        if (eventsByPointer[i]->GetNameOfTask() == nameTask && eventsByPointer[i]->GetColor() == colorTask)
        {
            Event *task = new Event ();
            task = eventsByPointer[i];

            //Сброс календаря
            QTextCharFormat formatCalendar;
            formatCalendar.setBackground(Qt::white);
            QDate dateCount = eventsByPointer[i]->GetStartDate();
            int day = dateCount.day();
            int month = dateCount.month();
            int year = dateCount.year();
            while (dateCount <= eventsByPointer[i]->GetFinishDate())
            {
                ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
                day++;
                if (day > dateCount.daysInMonth()) {month++; day = 1;}
                if (month > 12) {year++; month = 1;}
                dateCount.setDate(year, month, day);
            }
            //

            AddNewTask *customTaskWnd = new AddNewTask (this, task);
            customTaskWnd->exec();

            eventsByPointer[i] = task;      //Измененный объект

            FillCalendar();
            if(ui->tabWidgetMain->currentIndex() == 0) FillListUnderCalendar(task, task->GetColor());       //Только если открыт календарь (!!! НЕ РАБОТАЕТ, ДАЖЕ ЕСЛИ ТРУ, ХЗ ЧЕГО. ДЕБАЖИЛ, ТАМ ТОЧНО ТРУ!!!)
            FillTaskTable();
        }
    }
}
//



//Кнопка "Изменить задачу"
void MainWindow::on_pushButtonCustomTask_clicked()
{
    QString nameTask;
    QColor colorTask;

    //Получение названия задачи из календаря (выбрать задачу из списка под ним)
    if (ui->tabWidgetMain->currentIndex() == 0 && ui->listWidgetTasksForDay->selectedItems().count() != 0)
    {
        nameTask = ui->listWidgetTasksForDay->selectedItems().at(0)->text();

        //Выведение только имени из всего текста айтема и цвета
        short i = 0, count = 0;
        bool chkNameStart = false;
        QString buf = "";
        while (i < nameTask.length())
        {
            if (nameTask[i] == '"') {if (count == 0) i++; chkNameStart = true; count++;}
            if (nameTask[i] == '"' && count == 2) break;
            if (chkNameStart) buf += nameTask[i];
            i++;
        }
        nameTask = buf;
        colorTask = ui->listWidgetTasksForDay->selectedItems().at(0)->backgroundColor();
        //
    }
    //

        //Получение названия задачи из таблицы (выделить его)
        else if (ui->tabWidgetMain->currentIndex() == 1 && ui->tableWidgetMainTable->selectedItems().count() != 0)
        {
            nameTask = ui->tableWidgetMainTable->item(ui->tableWidgetMainTable->selectedItems().at(0)->row(), 0)->text();
            colorTask = ui->tableWidgetMainTable->item(ui->tableWidgetMainTable->selectedItems().at(0)->row(), 0)->textColor();
        }
        //
            else return;

    CustomTask(nameTask, colorTask);
}
//



//Функция заполнения календаря задачами
void MainWindow::FillCalendar()
{
    for (short i = 0; i < eventsByPointer.count(); i++)
    {
        QTextCharFormat formatCalendar;
        formatCalendar.setBackground(eventsByPointer[i]->GetColor());
        QDate dateCount = eventsByPointer[i]->GetStartDate();
        int day = dateCount.day();
        int month = dateCount.month();
        int year = dateCount.year();
        while (dateCount <= eventsByPointer[i]->GetFinishDate())
        {
            ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
            day++;
            if (day > dateCount.daysInMonth()) {month++; day = 1;}
            if (month > 12) {year++; month = 1;}
            dateCount.setDate(year, month, day);
        }
    }
}
//



//Функция заполнения списка задач под календарем (в случае двойного клика)
void MainWindow::FillListUnderCalendar(Event *task, QColor color)
{
    //В случае вызова функции редактирования задачи
    for (int i = 0; i < ui->listWidgetTasksForDay->count(); i++)
    {
        if (ui->listWidgetTasksForDay->item(i)->backgroundColor() == color)
        {
            on_calendarWidget_clicked (ui->calendarWidget->selectedDate());
            return;
        }
    }
    //

    //Обработка видимости кнопок добавления задачи на полях отображения информации
    ui->pushButtonAddTask_OnWidget->setVisible(false);
    ui->pushButtonAddTask_OnTable->setVisible(false);
    ui->labelAdd_OnCalendar->setVisible(false);
    ui->labelAdd_OnTable->setVisible(false);
    //

    QListWidgetItem *item =new QListWidgetItem();

    QString buf = "Задача: @" + task->GetNameOfTask() + "@\n\nОписание:\n" + task->GetDescriptionOfTask();
    buf.replace('@', '"');
    item->setText(buf);
    item->setBackground(color);
    ui->listWidgetTasksForDay->addItem(item);
}
//



//Функция заполнения таблицы задач
void MainWindow::FillTaskTable()
{
    QTableWidgetItem *tableItemName;
    QTableWidgetItem *tableItemStartDate;
    QTableWidgetItem *tableItemFinishDate;
    QTableWidgetItem *tableItemDescription;

    for (int i = 0; i < eventsByPointer.count(); i++)
    {
        tableItemName = new QTableWidgetItem ();
        tableItemStartDate = new QTableWidgetItem ();
        tableItemFinishDate = new QTableWidgetItem ();
        tableItemDescription = new QTableWidgetItem ();

        //Заполнение айтемов
        tableItemName->setText(eventsByPointer[i]->GetNameOfTask());
        tableItemName->setTextColor(eventsByPointer[i]->GetColor());
        tableItemStartDate->setText(eventsByPointer[i]->GetStartDate().toString("dd.MM.yyyy") + " в " + eventsByPointer[i]->GetStartTime().toString("hh:mm"));
        tableItemFinishDate->setText(eventsByPointer[i]->GetFinishDate().toString("dd.MM.yyyy") + " в " + eventsByPointer[i]->GetFinishTime().toString("hh:mm"));
        tableItemDescription->setText(eventsByPointer[i]->GetDescriptionOfTask());
        //

        //Установка айтемов
        ui->tableWidgetMainTable->setItem(i, 0, tableItemName);
        ui->tableWidgetMainTable->setItem(i, 1, tableItemStartDate);
        ui->tableWidgetMainTable->setItem(i, 2, tableItemFinishDate);
        ui->tableWidgetMainTable->setItem(i, 5, tableItemDescription);
        //
    }
}
//



//Функция заполнения списка задач под календарем
void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    QListWidgetItem *item =new QListWidgetItem();
    QTextCharFormat formatCalendar;

    for (short i = 0; i < eventsByPointer.count(); i++)
    {
        formatCalendar = ui->calendarWidget->dateTextFormat(date);
        if (formatCalendar.background().color() == eventsByPointer[i]->GetColor())
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
            QString buf = "Задача: @" + eventsByPointer[i]->GetNameOfTask() + "@\n\nОписание:\n" + eventsByPointer[i]->GetDescriptionOfTask();
            buf.replace('@', '"');
            item->setText(buf);
            item->setBackground(eventsByPointer[i]->GetColor());
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
    }
}
//



//Сброс списка задач под календарем во время смены даты
void MainWindow::on_calendarWidget_selectionChanged()
{
    ui->listWidgetTasksForDay->clear();
}
//



//Функция считывания данных из файла
void MainWindow::ReadFromFile()
{

}
//



//Функция записи данных в файл
void MainWindow::SaveToFile()
{

}
//



//Меню "Файл->Открыть..."
void MainWindow::on_actionOpen_triggered()
{
    ReadFromFile();
}
//



//Меню "Файл->Сохранить"
void MainWindow::on_actionSave_triggered()
{
    SaveToFile();
}
//



//Меню "Файл->Сохранить как..."
void MainWindow::on_actionSaveAs_triggered()
{
    SaveToFile();
}
//



//Функция удаления задачи
void MainWindow::DeleteTask(QString nameTask, QColor colorTask)
{
    for (int i = 0; i < eventsByPointer.count(); i++)
    {
        if (eventsByPointer[i]->GetNameOfTask() == nameTask && eventsByPointer[i]->GetColor() == colorTask)
        {
            //Сброс календаря
            QTextCharFormat formatCalendar;
            formatCalendar.setBackground(Qt::white);
            QDate dateCount = eventsByPointer[i]->GetStartDate();
            int day = dateCount.day();
            int month = dateCount.month();
            int year = dateCount.year();
            while (dateCount <= eventsByPointer[i]->GetFinishDate())
            {
                ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
                day++;
                if (day > dateCount.daysInMonth()) {month++; day = 1;}
                if (month > 12) {year++; month = 1;}
                dateCount.setDate(year, month, day);
            }
            //

            eventsByPointer.remove(i);      //Удаление конкретного элемента из вектора

            //Обработка видимости кнопок добавления задачи на полях отображения информации
            ui->listWidgetTasksForDay->clear();
            ui->pushButtonAddTask_OnWidget->setVisible(true);
            ui->pushButtonAddTask_OnTable->setVisible(true);
            ui->labelAdd_OnCalendar->setVisible(true);
            ui->labelAdd_OnTable->setVisible(true);
            ui->listWidgetTasksForDay->clear();
            //
            FillCalendar();

            ui->tableWidgetMainTable->removeRow(i);
            FillTaskTable();
        }
    }
}
//



//Кнопка "Удалить задачу"
void MainWindow::on_pushButtonDeleteTask_clicked()
{
    QString nameTask;
    QColor colorTask;

    //Получение названия задачи из календаря (выбрать задачу из списка под ним)
    if (ui->tabWidgetMain->currentIndex() == 0 && ui->listWidgetTasksForDay->selectedItems().count() != 0)
    {
        nameTask = ui->listWidgetTasksForDay->selectedItems().at(0)->text();

        //Выведение только имени из всего текста айтема и цвета
        short i = 0, count = 0;
        bool chkNameStart = false;
        QString buf = "";
        while (i < nameTask.length())
        {
            if (nameTask[i] == '"') {if (count == 0) i++; chkNameStart = true; count++;}
            if (nameTask[i] == '"' && count == 2) break;
            if (chkNameStart) buf += nameTask[i];
            i++;
        }
        nameTask = buf;
        colorTask = ui->listWidgetTasksForDay->selectedItems().at(0)->backgroundColor();
        //
    }
    //

        //Получение названия задачи из таблицы (выделить его)
        else if (ui->tabWidgetMain->currentIndex() == 1 && ui->tableWidgetMainTable->selectedItems().count() != 0)
        {
            nameTask = ui->tableWidgetMainTable->item(ui->tableWidgetMainTable->selectedItems().at(0)->row(), 0)->text();
            colorTask = ui->tableWidgetMainTable->item(ui->tableWidgetMainTable->selectedItems().at(0)->row(), 0)->textColor();
        }
        //
            else return;

    DeleteTask(nameTask, colorTask);
}
//
