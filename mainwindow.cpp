#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addnewtask.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
//



MainWindow::~MainWindow()
{
    delete ui;
}




//Функция открытия окна добавления новой задачи
void MainWindow::AddTask ()
{
    AddNewTask *AddTaskWindow = new AddNewTask(this);
    AddTaskWindow->exec();
}
//



//Кнопка "Добавить задачу"
void MainWindow::on_pushButtonAddTask_Main_clicked()
{
    AddTask();
}
//



//Кнопка "+"
void MainWindow::on_pushButtonAddTask_OnWidget_clicked()
{
    AddTask();
}
//
