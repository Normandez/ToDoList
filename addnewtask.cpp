#include "addnewtask.h"
#include "mainwindow.h"
#include "ui_addnewtask.h"
#include <QMessageBox>
#include <QDate>



//ВНИМАНИЕ!!! Комментированные куски кода не трогать!




AddNewTask::AddNewTask(QWidget *parent, QDate startDate, Event *objTask) :
    QDialog(parent),
    ui(new Ui::AddNewTask)
{
    ui->setupUi(this);

    sDate = startDate;
    obj = objTask;

    //Инициализация установки даты и времени
    ui->dateEditStartDate->setDate(sDate);
    ui->dateEditFinishDate->setDate(sDate);
    //

    //Инициализация комбобокса с повторением события
    ui->comboBoxRepeat->addItem("Однократно");
    ui->comboBoxRepeat->addItem("Ежедневно");
    ui->comboBoxRepeat->addItem("По будням");
    ui->comboBoxRepeat->addItem("Еженедельно");
    ui->comboBoxRepeat->addItem("Ежемесячно");
    ui->comboBoxRepeat->addItem("Ежегодно");
    //

    //Инициализация комбобокса с временем до напоминания о событии
    ui->comboBoxRemind->addItem("Нет");
    ui->comboBoxRemind->addItem("За 1 минуту");
    ui->comboBoxRemind->addItem("За 5 минут");
    ui->comboBoxRemind->addItem("За 10 минут");
    ui->comboBoxRemind->addItem("За 15 минут");
    ui->comboBoxRemind->addItem("За 20 минут");
    ui->comboBoxRemind->addItem("За 25 минут");
    ui->comboBoxRemind->addItem("За 30 минут");
    ui->comboBoxRemind->addItem("За 45 минут");
    ui->comboBoxRemind->addItem("За 1 час");
    ui->comboBoxRemind->addItem("За 2 часа");
    ui->comboBoxRemind->addItem("За 3 часа");
    ui->comboBoxRemind->addItem("За 12 часов");
    ui->comboBoxRemind->addItem("За 1 день");
    ui->comboBoxRemind->addItem("За 2 дня");
    ui->comboBoxRemind->addItem("За 1 неделю");
    //ui->comboBoxRemind->addItem("Настроить"); Можно оставить как расширение функционала на потом
    //
}



AddNewTask::AddNewTask(QWidget *parent, Event *objTask) :
    QDialog(parent),
    ui(new Ui::AddNewTask)
{
    ui->setupUi(this);

    obj = objTask;

    //Инициализация комбобокса с повторением события
    ui->comboBoxRepeat->addItem("Однократно");
    ui->comboBoxRepeat->addItem("Ежедневно");
    ui->comboBoxRepeat->addItem("По будням");
    ui->comboBoxRepeat->addItem("Еженедельно");
    ui->comboBoxRepeat->addItem("Ежемесячно");
    ui->comboBoxRepeat->addItem("Ежегодно");
    //

    //Инициализация комбобокса с временем до напоминания о событии
    ui->comboBoxRemind->addItem("Нет");
    ui->comboBoxRemind->addItem("За 1 минуту");
    ui->comboBoxRemind->addItem("За 5 минут");
    ui->comboBoxRemind->addItem("За 10 минут");
    ui->comboBoxRemind->addItem("За 15 минут");
    ui->comboBoxRemind->addItem("За 20 минут");
    ui->comboBoxRemind->addItem("За 25 минут");
    ui->comboBoxRemind->addItem("За 30 минут");
    ui->comboBoxRemind->addItem("За 45 минут");
    ui->comboBoxRemind->addItem("За 1 час");
    ui->comboBoxRemind->addItem("За 2 часа");
    ui->comboBoxRemind->addItem("За 3 часа");
    ui->comboBoxRemind->addItem("За 12 часов");
    ui->comboBoxRemind->addItem("За 1 день");
    ui->comboBoxRemind->addItem("За 2 дня");
    ui->comboBoxRemind->addItem("За 1 неделю");
    //ui->comboBoxRemind->addItem("Настроить"); Можно оставить как расширение функционала на потом
    //

    //Подгонка интерфейса под заданное событие
    ui->lineEditName->setText(obj->GetNameOfTask());
    ui->dateEditStartDate->setDate(obj->GetStartDate());
    ui->dateEditFinishDate->setDate(obj->GetFinishDate());
    ui->dateTimeEditStartTime->setTime(obj->GetStartTime());
    ui->dateTimeEditFinishTime->setTime(obj->GetFinishTime());
    //<Установка кратности>
    //<Установка напоминания>
    ui->plainTextEditDescription->setPlainText(obj->GetDescriptionOfTask());
    //
}



AddNewTask::~AddNewTask()
{
    delete ui;
}



//Переключатель "Весь день"
void AddNewTask::on_checkBox_toggled(bool checked)
{
    QPoint pointStartDate = ui->dateEditStartDate->pos();
    QPoint pointFinishDate = ui->dateEditFinishDate->pos();
    QPoint pointGroupBoxStart = ui->groupBoxStart->pos();
    QPoint pointGroupBoxFinish = ui->groupBoxFinish->pos();

    //Прячем ввод времени
    if (checked)
    {
        ui->dateTimeEditStartTime->setVisible(false);
        ui->dateTimeEditFinishTime->setVisible(false);
        ui->dateEditStartDate->setGeometry(pointStartDate.x(), pointStartDate.y(), 181, ui->dateEditStartDate->height());
        ui->dateEditFinishDate->setGeometry(pointFinishDate.x(), pointFinishDate.y(), 181, ui->dateEditFinishDate->height());
        ui->groupBoxStart->setGeometry(pointGroupBoxStart.x(), pointGroupBoxStart.y(), 183, ui->groupBoxStart->height());
        ui->groupBoxFinish->setGeometry(pointGroupBoxFinish.x(), pointGroupBoxFinish.y(), 183, ui->groupBoxFinish->height());

        ui->dateEditFinishDate->setDate(ui->dateEditStartDate->date());     //Устанавливаем одинаковые даты
    }
    //
        //Показываем ввод времени
        else
        {
            ui->dateTimeEditStartTime->setVisible(true);
            ui->dateTimeEditFinishTime->setVisible(true);
            ui->dateEditStartDate->setGeometry(pointStartDate.x(), pointStartDate.y(), 121, ui->dateEditStartDate->height());
            ui->dateEditFinishDate->setGeometry(pointFinishDate.x(), pointFinishDate.y(), 121, ui->dateEditFinishDate->height());
            ui->groupBoxStart->setGeometry(pointGroupBoxStart.x(), pointGroupBoxStart.y(), 123, ui->groupBoxStart->height());
            ui->groupBoxFinish->setGeometry(pointGroupBoxFinish.x(), pointGroupBoxFinish.y(), 123, ui->groupBoxFinish->height());
        }
        //
}
//



//Кнопка "Отмена"
void AddNewTask::on_pushButtonCancel_clicked()
{
    close();
}
//



//Кнопка "ОК"
void AddNewTask::on_pushButtonOK_clicked()
{
    QString buf = ui->plainTextEditDescription->toPlainText();
    buf.replace("\n", " ");

    obj->SetData(ui->lineEditName->text(), ui->dateEditStartDate->date(), ui->dateEditFinishDate->date(),
                 ui->dateTimeEditStartTime->time(), ui->dateTimeEditFinishTime->time(), buf);

    close();
}
//



//Обработка недопущения ввода конечной даты раньше начальной
void AddNewTask::on_dateEditFinishDate_dateChanged(const QDate &date)
{
    if (date < ui->dateEditStartDate->date()) ui->dateEditFinishDate->setDate(ui->dateEditStartDate->date());
}
//



//Обработка недопущения ввода конечного времени раньше начального в случае события в один и тот же день
void AddNewTask::on_dateTimeEditFinishTime_timeChanged(const QTime &time)
{
    if (ui->dateEditStartDate->date() == ui->dateEditFinishDate->date()
            && time < ui->dateTimeEditStartTime->time())
    {
        ui->dateTimeEditFinishTime->setTime(ui->dateTimeEditStartTime->time());
    }
}
//
