#include "remindwindow.h"
#include "ui_remindwindow.h"




RemindWindow::RemindWindow(QWidget *parent, QString name, QString dateAndTime, QColor color) :
    QDialog(parent),
    ui(new Ui::RemindWindow)
{
    ui->setupUi(this);

    //Фиксация полученных данных
    ui->labelName->setText(name);
    ui->labelName->setStyleSheet("QLabel{\ncolor: rgb(" + QString::number(color.red()) + ", " + QString::number(color.green()) + ", " + QString::number(color.blue()) + ");\n}");
    ui->labelStartDateAndTime->setText(dateAndTime);
    //
}




RemindWindow::~RemindWindow()
{
    delete ui;
}



//Кнопка "ОК"
void RemindWindow::on_pushButtonOK_clicked()
{
    close();
}
//
