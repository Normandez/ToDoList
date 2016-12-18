#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QDialog>



namespace Ui {
class HelpWindow;
}



class HelpWindow : public QDialog
{
    Q_OBJECT

private:
    Ui::HelpWindow *ui;

public:
    explicit HelpWindow(QWidget *parent = 0);
    ~HelpWindow();

private slots:
    void on_pushButtonOK_clicked();

};

#endif // HELPWINDOW_H
