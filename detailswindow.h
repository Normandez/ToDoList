#ifndef DETAILSWINDOW_H
#define DETAILSWINDOW_H

#include <QDialog>

namespace Ui {
class DetailsWindow;
}

class DetailsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DetailsWindow(QWidget *parent = 0);
    ~DetailsWindow();

private:
    Ui::DetailsWindow *ui;
};

#endif // DETAILSWINDOW_H
