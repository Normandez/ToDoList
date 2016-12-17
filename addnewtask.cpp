#include "addnewtask.h"
#include "ui_addnewtask.h"



//Конструктор добавления задачи
AddNewTask::AddNewTask(QWidget *parent, QDate startDate, Event *objTask, bool *cancel) :
    QDialog(parent),
    ui(new Ui::AddNewTask)
{
    ui->setupUi(this);

    sDate = startDate;
    obj = objTask;
    chkCancel = cancel;

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

    ui->comboBoxRepeat->setCurrentIndex(0);
    ui->comboBoxRepeat->setEnabled(true);
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
    //

    setWindowTitle("Добавить задачу");
}
//



//Конструктор изменения задачи
AddNewTask::AddNewTask(QWidget *parent, Event *objTask, bool *cancel) :
    QDialog(parent),
    ui(new Ui::AddNewTask)
{
    ui->setupUi(this);

    obj = objTask;
    chkCancel = cancel;

    //Инициализация комбобокса с повторением события
    ui->comboBoxRepeat->addItem("Однократно");      //0
    ui->comboBoxRepeat->addItem("Ежедневно");       //1
    ui->comboBoxRepeat->addItem("По будням");       //2
    ui->comboBoxRepeat->addItem("Еженедельно");     //3
    ui->comboBoxRepeat->addItem("Ежемесячно");      //4
    ui->comboBoxRepeat->addItem("Ежегодно");        //5
    ui->comboBoxRepeat->setCurrentIndex(0);
    //

    //Инициализация комбобокса с временем до напоминания о событии
    ui->comboBoxRemind->addItem("Нет");                         //0
    ui->comboBoxRemind->addItem("За 1 минуту");                 //1
    ui->comboBoxRemind->addItem("За 5 минут");                  //2
    ui->comboBoxRemind->addItem("За 10 минут");                 //3
    ui->comboBoxRemind->addItem("За 15 минут");                 //4
    ui->comboBoxRemind->addItem("За 20 минут");                 //5
    ui->comboBoxRemind->addItem("За 25 минут");                 //6
    ui->comboBoxRemind->addItem("За 30 минут");                 //7
    ui->comboBoxRemind->addItem("За 45 минут");                 //8
    ui->comboBoxRemind->addItem("За 1 час");                    //9
    ui->comboBoxRemind->addItem("За 2 часа");                   //10
    ui->comboBoxRemind->addItem("За 3 часа");                   //11
    ui->comboBoxRemind->addItem("За 12 часов");                 //12
    ui->comboBoxRemind->addItem("За 1 день");                   //13
    ui->comboBoxRemind->addItem("За 2 дня");                    //14
    ui->comboBoxRemind->addItem("За 1 неделю");                 //15
    //ui->comboBoxRemind->addItem("Настроить"); Можно оставить как расширение функционала на потом
    //

    //Подгонка интерфейса под заданное событие
    ui->lineEditName->setText(obj->GetNameOfTask());
    ui->dateEditStartDate->setDate(obj->GetStartDate());
    ui->dateEditFinishDate->setDate(obj->GetFinishDate());
    ui->dateTimeEditStartTime->setTime(obj->GetStartTime());
    ui->dateTimeEditFinishTime->setTime(obj->GetFinishTime());
    ui->comboBoxRepeat->setCurrentIndex(obj->GetRepeatOfTask());
    ui->comboBoxRemind->setCurrentIndex(obj->GetRemindOfTask());
    ui->plainTextEditDescription->setPlainText(obj->GetDescriptionOfTask());
    //

    //Проверка однократности задачи
    if (ui->dateEditStartDate->date() != ui->dateEditFinishDate->date())
    {
        ui->comboBoxRepeat->setCurrentIndex(0);
        ui->comboBoxRepeat->setEnabled(false);
    }
        else ui->comboBoxRepeat->setEnabled(true);
    //

    setWindowTitle("Изменить задачу");
}
//



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
    *chkCancel = true;

    close();
}
//



//Кнопка "ОК"
void AddNewTask::on_pushButtonOK_clicked()
{
    QString buf = ui->plainTextEditDescription->toPlainText();
    buf.replace("\n", " ");

    obj->SetData(ui->lineEditName->text(), ui->dateEditStartDate->date(), ui->dateEditFinishDate->date(),
                 ui->dateTimeEditStartTime->time(), ui->dateTimeEditFinishTime->time(), ui->comboBoxRepeat->currentIndex(), ui->comboBoxRemind->currentIndex(), buf);

    *chkCancel = false;

    close();
}
//



//Обработка ввода начальной даты
void AddNewTask::on_dateEditStartDate_dateChanged(const QDate &date)
{
    if (date > ui->dateEditFinishDate->date()) ui->dateEditFinishDate->setDate(ui->dateEditStartDate->date());       //Недопущение ввода конечной даты меньше начальной

    //Условие однократности события
    if (date != ui->dateEditFinishDate->date())
    {
        ui->comboBoxRepeat->setCurrentIndex(0);
        ui->comboBoxRepeat->setEnabled(false);
        return;
    }
    //

    //Условие неоднократности события
    if (date == ui->dateEditFinishDate->date())
    {
        ui->comboBoxRepeat->setEnabled (true);
        return;
    }
    //
}
//



//Обработка ввода конечной даты
void AddNewTask::on_dateEditFinishDate_dateChanged(const QDate &date)
{
    if (date < ui->dateEditStartDate->date()) {ui->dateEditFinishDate->setDate(ui->dateEditStartDate->date()); ui->comboBoxRepeat->setEnabled(true); return;}       //Недопущение ввода конечной даты меньше начальной

    //Условие однократности события
    if (date != ui->dateEditStartDate->date())
    {
        ui->comboBoxRepeat->setCurrentIndex(0);
        ui->comboBoxRepeat->setEnabled(false);
        return;
    }
    //

    //Условие неоднократности события
    if (date == ui->dateEditStartDate->date())
    {
        ui->comboBoxRepeat->setEnabled(true);
        return;
    }
    //
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



//Проверка отсутствия имени задачи
void AddNewTask::on_lineEditName_textChanged(const QString &arg1)
{
    if (arg1.length() == 0) ui->pushButtonOK->setEnabled(false);
        else ui->pushButtonOK->setEnabled(true);
}
//
