#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "event.h"
#include "addnewtask.h"
#include "remindwindow.h"
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

    //Инициализация таймера контроля напоминания
    mainTimer = new QTimer ();
    connect(mainTimer, SIGNAL(timeout()), this, SLOT(mainTimer_overflow()));
    mainTimer->start(5000);
    //

    //Инициализация ТулБара
    ui->mainToolBar->addAction(ui->actionToday);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionAddTask);
    ui->mainToolBar->addAction(ui->actionCustomTask);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionDeleteTask);
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
    bool *chkCancel = new bool;
    Event *task = new Event();      //Создаем объект класса задачи

    AddNewTask *AddTaskWindow = new AddNewTask(this, ui->calendarWidget->selectedDate(), task, chkCancel);
    AddTaskWindow->exec();

    //Проверка нажатия отмены на окне создания новой задачи
    if (*chkCancel)
    {
        task->destroyed();
        return;
    }
    //

    ui->actionClose->setEnabled(true);

    task->SetColor(QColor(rand()%255+1, rand()%255+1, rand()%255+1));       //Случайный выбор цвета

    task->SetRemind();

    eventsByPointer.push_back(task);

    FillCalendar();      //Заполнение календаря

    if (doubleClickChk) {FillListUnderCalendar(task, task->GetColor()); doubleClickChk = false;}     //Заполнения списка под календарем

    ui->tableWidgetMainTable->insertRow(ui->tableWidgetMainTable->rowCount());      //Вставка строки

    FillTaskTable();        //Заполнение таблицы
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
            bool *chkCancel = new bool;
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

            AddNewTask *customTaskWnd = new AddNewTask (this, task, chkCancel);
            customTaskWnd->exec();

            task->SetRemindComplete(0);     //Сброс совершённости напоминания

            FillCalendar();

            //Проверка нажатия отмены на окне редактирования задачи
            if (*chkCancel)
            {
                task->destroyed();
                delete chkCancel;
                continue;
            }
            //

            task->SetRemind();

            eventsByPointer[i] = task;      //Измененный объект

            if(ui->tabWidgetMain->currentIndex() == 0) FillListUnderCalendar(task, task->GetColor());       //Только если открыт календарь (!!! НЕ РАБОТАЕТ, ДАЖЕ ЕСЛИ ТРУ, ХЗ ЧЕГО. ДЕБАЖИЛ, ТАМ ТОЧНО ТРУ!!!)
            FillTaskTable();
        }
    }
}
//



//Функция заполнения календаря задачами
void MainWindow::FillCalendar()
{
    QTextCharFormat formatCalendar;

    for (short i = 0; i < eventsByPointer.count(); i++)
    {
        //Если событие однократное
        if (eventsByPointer[i]->GetRepeatOfTask() == 0)
        {
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

        //Если событие ежедневное
        if (eventsByPointer[i]->GetRepeatOfTask() == 1)
        {
            formatCalendar.setBackground(eventsByPointer[i]->GetColor());
            QDate dateCount = eventsByPointer[i]->GetStartDate();
            int day = dateCount.day();
            int month = dateCount.month();
            int year = dateCount.year();
            while (dateCount.year() <= 2026)
            {
                ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
                day++;
                if (day > dateCount.daysInMonth()) {month++; day = 1;}
                if (month > 12) {year++; month = 1;}
                dateCount.setDate(year, month, day);
            }
        }
        //

        //Если событие происходит по будням
        if (eventsByPointer[i]->GetRepeatOfTask() == 2)
        {
            formatCalendar.setBackground(eventsByPointer[i]->GetColor());
            QDate dateCount = eventsByPointer[i]->GetStartDate();
            int day = dateCount.day();
            int month = dateCount.month();
            int year = dateCount.year();
            while (dateCount.year() <= 2026)
            {
                if (dateCount.dayOfWeek() != 6 && dateCount.dayOfWeek() != 7)ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
                day++;
                if (day > dateCount.daysInMonth()) {month++; day = 1;}
                if (month > 12) {year++; month = 1;}
                dateCount.setDate(year, month, day);
            }
        }
        //

        //Если событие происходит еженедельно
        if (eventsByPointer[i]->GetRepeatOfTask() == 3)
        {
            formatCalendar.setBackground(eventsByPointer[i]->GetColor());
            QDate dateCount = eventsByPointer[i]->GetStartDate();
            int day = dateCount.day();
            int month = dateCount.month();
            int year = dateCount.year();
            int dayOfWeek = dateCount.dayOfWeek();
            while (dateCount.year() <= 2026)
            {
                if (dateCount.dayOfWeek() == dayOfWeek)ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
                day++;
                if (day > dateCount.daysInMonth()) {month++; day = 1;}
                if (month > 12) {year++; month = 1;}
                dateCount.setDate(year, month, day);
            }
        }
        //

        //Если событие происходит ежемесечно
        if (eventsByPointer[i]->GetRepeatOfTask() == 4)
        {
            formatCalendar.setBackground(eventsByPointer[i]->GetColor());
            QDate dateCount = eventsByPointer[i]->GetStartDate();
            int day = dateCount.day();
            int month = dateCount.month();
            int year = dateCount.year();
            int dayOfMonth = dateCount.day();
            while (dateCount.year() <= 2026)
            {
                if (dateCount.daysInMonth() < dayOfMonth)
                {
                    dateCount.setDate(year, month, dateCount.daysInMonth());
                    ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
                }
                if (dateCount.day() == dayOfMonth) ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
                day++;
                if (day > dateCount.daysInMonth()) {month++; day = 1;}
                if (month > 12) {year++; month = 1;}
                dateCount.setDate(year, month, day);
            }
        }
        //

        //Если событие происходит ежегодно
        if (eventsByPointer[i]->GetRepeatOfTask() == 5)
        {
            formatCalendar.setBackground(eventsByPointer[i]->GetColor());
            QDate dateCount = eventsByPointer[i]->GetStartDate();
            int day = dateCount.day();
            int month = dateCount.month();
            int year = dateCount.year();
            int dayOfMonth = dateCount.day();
            int monthOfYear = dateCount.month();
            while (dateCount.year() <= 2026)
            {
                if (dateCount.month() == monthOfYear && dateCount.daysInMonth() < dayOfMonth)
                {
                    dateCount.setDate(year, month, dateCount.daysInMonth());
                    ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
                }
                if (dateCount.month() == monthOfYear && dateCount.day() == dayOfMonth) ui->calendarWidget->setDateTextFormat(dateCount, formatCalendar);
                day++;
                if (day > dateCount.daysInMonth()) {month++; day = 1;}
                if (month > 12) {year++; month = 1;}
                dateCount.setDate(year, month, day);
            }
        }
        //
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
    QTableWidgetItem *tableItemRepeat;
    QTableWidgetItem *tableItemRemind;
    QTableWidgetItem *tableItemDescription;
    QString repeat;
    QString remind;

    for (int i = 0; i < eventsByPointer.count(); i++)
    {
        tableItemName = new QTableWidgetItem ();
        tableItemStartDate = new QTableWidgetItem ();
        tableItemFinishDate = new QTableWidgetItem ();
        tableItemRepeat = new QTableWidgetItem ();
        tableItemRemind = new QTableWidgetItem ();
        tableItemDescription = new QTableWidgetItem ();

        //Заполнение айтемов
        tableItemName->setText(eventsByPointer[i]->GetNameOfTask());
        tableItemName->setTextColor(eventsByPointer[i]->GetColor());
        tableItemStartDate->setText(eventsByPointer[i]->GetStartDate().toString("dd.MM.yyyy") + " в " + eventsByPointer[i]->GetStartTime().toString("hh:mm"));
        tableItemFinishDate->setText(eventsByPointer[i]->GetFinishDate().toString("dd.MM.yyyy") + " в " + eventsByPointer[i]->GetFinishTime().toString("hh:mm"));
        //Расшифровка кратности
        repeat = QString::number(eventsByPointer[i]->GetRepeatOfTask());
        repeat.replace("0","Однократно");
        repeat.replace("1","Ежедневно");
        repeat.replace("2","По будням");
        repeat.replace("3","Еженедельно");
        repeat.replace("4","Ежемесячно");
        repeat.replace("5","Ежегодно");
        //
        tableItemRepeat->setText(repeat);
        //Расшифровка напоминания
        remind = QString::number(eventsByPointer[i]->GetRemindOfTask());
        remind.replace("0","Нет");
        remind.replace("1","За 1 минуту");
        remind.replace("2","За 5 минут");
        remind.replace("3","За 10 минут");
        remind.replace("4","За 15 минут");
        remind.replace("5","За 20 минут");
        remind.replace("6","За 25 минут");
        remind.replace("7","За 30 минут");
        remind.replace("8","За 45 минут");
        remind.replace("9","За 1 час");
        remind.replace("10","За 2 часа");
        remind.replace("11","За 3 часа");
        remind.replace("12","За 12 часов");
        remind.replace("13","За 1 день");
        remind.replace("14","За 2 дня");
        remind.replace("15","За 1 неделю");
        tableItemRemind->setText(remind);
        //
        tableItemDescription->setText(eventsByPointer[i]->GetDescriptionOfTask());
        //

        //Установка айтемов
        ui->tableWidgetMainTable->setItem(i, 0, tableItemName);
        ui->tableWidgetMainTable->setItem(i, 1, tableItemStartDate);
        ui->tableWidgetMainTable->setItem(i, 2, tableItemFinishDate);
        ui->tableWidgetMainTable->setItem(i, 3, tableItemRepeat);
        ui->tableWidgetMainTable->setItem(i, 4, tableItemRemind);
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
void MainWindow::ReadFromFile(QString openFileName)
{
    if (openFileName.length() != 0) DeleteAllTasks();       //Предварительная очистка интерфейса

    //XML Чтение
    if(openFileName.indexOf(".xml") > 0)
    {
        Event *objXML;

        QFile fileXML(openFileName);
        if(!fileXML.open(QFile::ReadOnly | QFile::Text))
            QMessageBox::warning(this,
                                  "Ошибка файла",
                                  "Не удалось открыть файл",
                                  QMessageBox::Ok);
        else
        {
            QXmlStreamReader xmlReader;
            xmlReader.setDevice(&fileXML);

            while(!xmlReader.atEnd())
            {

                if(xmlReader.isStartElement() && xmlReader.name() != "resources")
                {
                    objXML = new Event ();
                    if(xmlReader.name() == "NameOfEvent")
                    {
                        objXML->SetNameOfTask(xmlReader.readElementText());
                        xmlReader.readNextStartElement();
                    }
                    if(xmlReader.name() == "StartDate")
                    {
                        objXML->SetStartDate(xmlReader.readElementText());
                        xmlReader.readNextStartElement();
                    }
                    if(xmlReader.name() == "FinishDate")
                    {
                        objXML->SetFinishDate(xmlReader.readElementText());
                        xmlReader.readNextStartElement();
                    }
                    if(xmlReader.name() == "StartTime")
                    {
                        objXML->SetStartTime(xmlReader.readElementText());
                        xmlReader.readNextStartElement();
                    }
                    if(xmlReader.name() == "FinishTime")
                    {
                        objXML->SetFinishTime(xmlReader.readElementText());
                        xmlReader.readNextStartElement();
                    }

                    if(xmlReader.name() == "RemindDate")
                    {
                        objXML->SetRemindDate(xmlReader.readElementText());
                        xmlReader.readNextStartElement();
                    }

                    if(xmlReader.name() == "RemindTime")
                    {
                        objXML->SetRemindTime(xmlReader.readElementText());
                        xmlReader.readNextStartElement();
                    }

                    if(xmlReader.name() == "RepeatOfTask")
                    {
                        objXML->SetRepeatOfTask(xmlReader.readElementText().toInt());
                        xmlReader.readNextStartElement();
                    }

                    if(xmlReader.name() == "RemindOfTask")
                    {
                        objXML->SetRemindOfTask(xmlReader.readElementText().toInt());
                        xmlReader.readNextStartElement();
                    }

                    if(xmlReader.name() == "RemindComplete")
                    {
                        objXML->SetRemindComplete(xmlReader.readElementText().toInt());
                        xmlReader.readNextStartElement();
                    }


                    if(xmlReader.name() == "Description")
                    {
                        objXML->SetDescriptionOfTask(xmlReader.readElementText());
                        xmlReader.readNextStartElement();
                    }
                    if(xmlReader.name() == "Color")
                    {
                        objXML->SetColor(xmlReader.readElementText());
                        objXML->SetRemindComplete(0);
                        xmlReader.readNextStartElement();
                        eventsByPointer.push_back(objXML);
                        ui->tableWidgetMainTable->insertRow(ui->tableWidgetMainTable->rowCount());      //Вставка строки в таблицу
                    }
                }

                xmlReader.readNext();
            }
            fileXML.close();

            FillCalendar();
            FillTaskTable();
        }
        return;
    }
    //

    //JSON Чтение
    if(openFileName.indexOf(".json") > 0)
    {
        Event *objJSON;
        QFile fileJSON(openFileName);
        if (!fileJSON.open(QIODevice::ReadOnly))
        {
            qWarning("Couldn't open save file.");
            return;
        }

        QByteArray saveData = fileJSON.readAll();
        QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
        QJsonObject json = loadDoc.object();

        for(int i = 0; i < json["CountOfEvents"].toInt(); i++)
        {
            objJSON  = new Event ();
            QJsonArray nEvent = json["Event_" + QString::number(i+1)].toArray();

            objJSON->SetNameOfTask(nEvent[0].toString());
            objJSON->SetStartDate(nEvent[1].toString());
            objJSON->SetFinishDate(nEvent[2].toString());
            objJSON->SetStartTime(nEvent[3].toString());
            objJSON->SetFinishTime(nEvent[4].toString());

            objJSON->SetRemindDate(nEvent[5].toString());
            objJSON->SetRemindTime(nEvent[6].toString());
            objJSON->SetRepeatOfTask(nEvent[7].toInt());
            objJSON->SetRemindOfTask(nEvent[8].toInt());
            objJSON->SetRemindComplete(nEvent[9].toInt());

            objJSON->SetDescriptionOfTask(nEvent[10].toString());
            objJSON->SetColor(nEvent[11].toString());

            objJSON->SetRemindComplete(0);
            eventsByPointer.push_back(objJSON);
            ui->tableWidgetMainTable->insertRow(ui->tableWidgetMainTable->rowCount());      //Вставка строки в таблицу

        }
        fileJSON.close();

        FillCalendar();
        FillTaskTable();

        return;
    }
    //
}
//



//Функция записи данных в файл
void MainWindow::SaveToFile(QString saveFileName)
{
    //ЗАПИСЬ В XML ФАЙЛ
    if (saveFileName.indexOf(".xml") > 0)
    {
        QFile fileXML(saveFileName);
        fileXML.open(QIODevice::WriteOnly | QIODevice::Truncate);

        QXmlStreamWriter xmlWriter(&fileXML);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("resources");

        QString ev;
        for(int i = 0; i < eventsByPointer.count(); i++)
        {
            ev = "Event_";
            ev = ev.append(QString::number(i + 1));
            xmlWriter.writeStartElement(ev);
            xmlWriter.writeTextElement("NameOfEvent", eventsByPointer[i]->GetNameOfTask());
            xmlWriter.writeTextElement("StartDate", eventsByPointer[i]->GetStartDate().toString("dd.MM.yyyy"));
            xmlWriter.writeTextElement("FinishDate",eventsByPointer[i]->GetFinishDate().toString("dd.MM.yyyy"));
            xmlWriter.writeTextElement("StartTime", eventsByPointer[i]->GetStartTime().toString("hh:mm"));
            xmlWriter.writeTextElement("FinishTime", eventsByPointer[i]->GetFinishTime().toString("hh:mm"));
            xmlWriter.writeTextElement("RemindDate", eventsByPointer[i]->GetRemindDate().toString("dd.MM.yyyy"));
            xmlWriter.writeTextElement("RemindTime", eventsByPointer[i]->GetRemindTime().toString("hh:mm"));
            xmlWriter.writeTextElement("RepeatOfTask", QString::number(eventsByPointer[i]->GetRepeatOfTask()));
            xmlWriter.writeTextElement("RemindOfTask", QString::number(eventsByPointer[i]->GetRemindOfTask()));
            xmlWriter.writeTextElement("RemindComplete", QString::number(eventsByPointer[i]->GetRemindComplete()));
            xmlWriter.writeTextElement("Description", eventsByPointer[i]->GetDescriptionOfTask());
            xmlWriter.writeTextElement("Color",  eventsByPointer[i]->GetColor().name());
            xmlWriter.writeEndElement();
        }
        xmlWriter.writeEndDocument();
        fileXML.close();

        return;
    }
    //

    //ЗАПИСЬ В JSON
    if (saveFileName.indexOf(".json") > 0)
    {
        QFile fileJSON(saveFileName);
        if (!fileJSON.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qWarning("Couldn't open save file.");
            return;
        }

        QJsonObject json;
        json["CountOfEvents"] = eventsByPointer.count();
        for(int i = 0; i < eventsByPointer.count(); i++)
        {
            QJsonArray data;
            data.append(eventsByPointer[i]->GetNameOfTask());
            data.append(eventsByPointer[i]->GetStartDate().toString("dd.MM.yyyy"));
            data.append(eventsByPointer[i]->GetFinishDate().toString("dd.MM.yyyy"));
            data.append(eventsByPointer[i]->GetStartTime().toString("hh:mm"));
            data.append(eventsByPointer[i]->GetFinishTime().toString("hh:mm"));
            data.append(eventsByPointer[i]->GetRemindDate().toString("dd.MM.yyyy"));
            data.append(eventsByPointer[i]->GetRemindTime().toString("hh:mm"));
            data.append(eventsByPointer[i]->GetRepeatOfTask());
            data.append(eventsByPointer[i]->GetRemindOfTask());
            data.append(eventsByPointer[i]->GetRemindComplete());
            data.append(eventsByPointer[i]->GetDescriptionOfTask());
            data.append(eventsByPointer[i]->GetColor().name());
            json["Event_" + QString::number(i+1)] = data;
        }
        QJsonDocument saveDoc(json);
        fileJSON.write(saveDoc.toJson());
        fileJSON.close();

        return;
    }
    //
}
//



//Меню "Файл->Открыть..."
void MainWindow::on_actionOpen_triggered()
{
    ui->actionSave->setEnabled(true);
    ui->actionClose->setEnabled(true);

    QFileDialog *openFileDialog = new QFileDialog (this);
    fileName = openFileDialog->getOpenFileName(this, "Открыть...", ".\\", tr("XML (*.xml);;JSON (*.json)" ));
    ReadFromFile(fileName);
}
//



//Меню "Файл->Сохранить"
void MainWindow::on_actionSave_triggered()
{
    SaveToFile(fileName);
}
//



//Меню "Файл->Сохранить как..."
void MainWindow::on_actionSaveAs_triggered()
{
    ui->actionSave->setEnabled(true);

    QFileDialog *saveFileDialog = new QFileDialog (this);
    fileName = saveFileDialog->getSaveFileName (this, "Сохранить как...", ".\\", tr("XML (*.xml);;JSON (*.json)" ));
    SaveToFile(fileName);
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

            eventsByPointer[i]->destroyed();        //Удаление самого указателя (объекта)
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



//Обработка напоминания таймером
void MainWindow::mainTimer_overflow()
{
    for (int i = 0; i < eventsByPointer.count(); i++)
    {
        if (eventsByPointer[i]->GetRemindOfTask() != 0 &&  eventsByPointer[i]->GetRemindComplete() == 0 && eventsByPointer[i]->GetRemindDate() == QDate::currentDate() && eventsByPointer[i]->GetRemindTime().toString("hh:mm") == QTime::currentTime().toString("hh:mm"))
        {
            //Основные данные напоминания
            QString name = eventsByPointer[i]->GetNameOfTask();
            QColor color = eventsByPointer[i]->GetColor();
            QString dateAndTime = eventsByPointer[i]->GetStartDate().toString("dd.MM.yyyy") + " в " + eventsByPointer[i]->GetStartTime().toString("hh:mm");
            //

            RemindWindow *remindWnd = new RemindWindow (this, name, dateAndTime, color);
            remindWnd->show();

            eventsByPointer[i]->SetRemindComplete(1);     //Напоминание совершено
        }
    }
}
//



//Меню Файл->Выход
void MainWindow::on_actionExit_triggered()
{
    close();
}
//



//Функция очистки всего интерфейса
void MainWindow::DeleteAllTasks ()
{
    for (int i = 0; i < eventsByPointer.count(); i++)
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

        eventsByPointer[i]->destroyed();        //Удаление самого указателя (объекта)

        //Обработка видимости кнопок добавления задачи на полях отображения информации
        ui->listWidgetTasksForDay->clear();
        ui->pushButtonAddTask_OnWidget->setVisible(true);
        ui->pushButtonAddTask_OnTable->setVisible(true);
        ui->labelAdd_OnCalendar->setVisible(true);
        ui->labelAdd_OnTable->setVisible(true);
        ui->listWidgetTasksForDay->clear();
        //
    }

    int i = ui->tableWidgetMainTable->rowCount();
    while (i >= 0) {ui->tableWidgetMainTable->removeRow(i); i--;}
    eventsByPointer.clear();
}
//



//Меню Файл->Закрыть
void MainWindow::on_actionClose_triggered()
{
    fileName = "";
    ui->actionSave->setEnabled(false);
    ui->actionClose->setEnabled(false);

    DeleteAllTasks();
}
//



//Действие при активации айтема под календарем
void MainWindow::on_listWidgetTasksForDay_itemSelectionChanged()
{
    if (ui->listWidgetTasksForDay->selectedItems().count() != 0) {ui->actionCustomTask->setEnabled(true); ui->actionDeleteTask->setEnabled(true);}
        else {ui->actionCustomTask->setEnabled(false); ui->actionDeleteTask->setEnabled(false);}
}
//



//Действие при активации айтема в таблице
void MainWindow::on_tableWidgetMainTable_itemSelectionChanged()
{
    if (ui->tableWidgetMainTable->selectedItems().count() != 0) {ui->actionCustomTask->setEnabled(true); ui->actionDeleteTask->setEnabled(true);}
        else {ui->actionCustomTask->setEnabled(false); ui->actionDeleteTask->setEnabled(false);}
}
//



//Действие при изменении закладки
void MainWindow::on_tabWidgetMain_currentChanged(int index)
{
    //Выбрана закладка с календарем
    if (index == 0)
    {
        ui->actionToday->setEnabled(true);
        if (ui->listWidgetTasksForDay->selectedItems().count() != 0) {ui->actionCustomTask->setEnabled(true); ui->actionDeleteTask->setEnabled(true);}
            else {ui->actionCustomTask->setEnabled(false); ui->actionDeleteTask->setEnabled(false);}
    }
    //

    //Выбрана закладка с таблицей
    if (index == 1)
    {
        ui->actionToday->setEnabled(false);
        if (ui->tableWidgetMainTable->selectedItems().count() != 0) {ui->actionCustomTask->setEnabled(true); ui->actionDeleteTask->setEnabled(true);}
            else {ui->actionCustomTask->setEnabled(false); ui->actionDeleteTask->setEnabled(false);}
    }
    //
}
//



//Меню Инструменты->Сегодня
void MainWindow::on_actionToday_triggered()
{
    QDate today = QDate::currentDate();;
    ui->calendarWidget->setSelectedDate(today);
    ui->calendarWidget->setFocus();

    on_calendarWidget_clicked(today);       //Выдача списка задач если они есть
}
//



//Меню Инструменты->Добавить задачу
void MainWindow::on_actionAddTask_triggered()
{
    AddTask();
}
//



//Функция выделения в памяти конкретной задачи
void MainWindow::SelectCurrentTask (QString *nameTaskPointer, QColor *colorTaskPointer)
{
    QString nameTask = *nameTaskPointer;
    QColor colorTask = *colorTaskPointer;

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

        *nameTaskPointer = nameTask;
        *colorTaskPointer = colorTask;
        //
    }
    //

        //Получение названия задачи из таблицы (выделить его)
        else if (ui->tabWidgetMain->currentIndex() == 1 && ui->tableWidgetMainTable->selectedItems().count() != 0)
        {
            nameTask = ui->tableWidgetMainTable->item(ui->tableWidgetMainTable->selectedItems().at(0)->row(), 0)->text();
            colorTask = ui->tableWidgetMainTable->item(ui->tableWidgetMainTable->selectedItems().at(0)->row(), 0)->textColor();

            *nameTaskPointer = nameTask;
            *colorTaskPointer = colorTask;
        }
        //
            else return;
}
//



//Меню Инструменты->Изменить задачу
void MainWindow::on_actionCustomTask_triggered()
{
    QString *nameTask = new QString ();
    QColor *colorTask = new QColor ();
    SelectCurrentTask(nameTask, colorTask);

    CustomTask(*nameTask, *colorTask);
}
//



//Меню Инструменты->Удалить задачу
void MainWindow::on_actionDeleteTask_triggered()
{
    QString *nameTask = new QString ();
    QColor *colorTask = new QColor ();
    SelectCurrentTask(nameTask, colorTask);

    DeleteTask(*nameTask, *colorTask);
}
//
