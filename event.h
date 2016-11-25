#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QDate>



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

public:
    explicit Event(); //конструктор без комментария
    ~Event (){}
    void SetData (QString name, QDate sDate, QDate fDate,
                  QTime sTime, QTime fTime, QString descript);
    QString GetNameOfTask();
    QDate GetStartDate();
    QDate GetFinishDate();
    QTime GetStartTime();
    QTime GetFinishTime();
    QString GetDescriptionOfTask();
};
//

#endif // EVENT_H
