#ifndef REMINDWINDOW_H
#define REMINDWINDOW_H

#include <QDialog>




namespace Ui {
class RemindWindow;
}




class RemindWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RemindWindow(QWidget *parent, QString name, QString dateAndTime, QColor color);
    ~RemindWindow();

private slots:
    void on_pushButtonOK_clicked();

private:
    Ui::RemindWindow *ui;
};

#endif // REMINDWINDOW_H
