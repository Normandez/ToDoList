#include "addnewtask.h"
#include "ui_addnewtask.h"

AddNewTask::AddNewTask(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewTask)
{
    ui->setupUi(this);

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
