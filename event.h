#ifndef EVENT_H
#define EVENT_H
<<<<<<< HEAD

#include <QObject>
#include <QDate>
#include <QColor>



class Event : public QObject     //класс события
=======
<<<<<<< HEAD
#include <QString>
struct date
>>>>>>> ForMerging
{
    Q_OBJECT

private:
    QString nameOfTask;
    QDate startDate;
    QDate finishDate;
    QTime startTime;
    QTime finishTime;
    //<???> repeatOfTask;
    //<???> remindOfTask;
    QString descriptionOfTask;      //описание задачи
    QColor color;

public:
    Event(); //конструктор без комментария
    ~Event (){}
    void SetData (QString name, QDate sDate, QDate fDate,
                  QTime sTime, QTime fTime, QString descript);
    void SetColor (QColor clr);
    QString GetNameOfTask();
    QDate GetStartDate();
    QDate GetFinishDate();
    QTime GetStartTime();
    QTime GetFinishTime();
    QString GetDescriptionOfTask();
    QColor GetColor();
};
//
<<<<<<< HEAD

=======
=======

#include <QObject>
#include <QDate>
#include <QColor>



class Event : public QObject     //класс события
{
    Q_OBJECT

private:
    QString nameOfTask;
    QDate startDate;
    QDate finishDate;
    QTime startTime;
    QTime finishTime;
    //<???> repeatOfTask;
    //<???> remindOfTask;
    QString descriptionOfTask;      //описание задачи
    QColor color;

public:
    Event(); //конструктор без комментария
    ~Event (){}
    void SetData (QString name, QDate sDate, QDate fDate,
                  QTime sTime, QTime fTime, QString descript);
    void SetColor (QColor clr);
    QString GetNameOfTask();
    QDate GetStartDate();
    QDate GetFinishDate();
    QTime GetStartTime();
    QTime GetFinishTime();
    QString GetDescriptionOfTask();
    QColor GetColor();

    void SetColor (QString);
    void SetNameOfTask(QString);
    void SetStartDate(QString);
    void SetFinishDate(QString);
    void SetStartTime(QString);
    void SetFinishTime(QString);
    void SetDescriptionOfTask(QString);
};
//

>>>>>>> b126979570160e1560f69ca775275d0c5a803563
>>>>>>> ForMerging
#endif // EVENT_H
