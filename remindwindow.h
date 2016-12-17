#ifndef REMINDWINDOW_H
#define REMINDWINDOW_H

#include <QDialog>



namespace Ui {
class RemindWindow;
}



class RemindWindow : public QDialog     //Класс формы окна напоминания
{
    Q_OBJECT

private:
    Ui::RemindWindow *ui;

public:
    explicit RemindWindow(QWidget *parent, QString name, QString dateAndTime, QColor color);
    ~RemindWindow();

private slots:
    void on_pushButtonOK_clicked();

};

#endif // REMINDWINDOW_H
