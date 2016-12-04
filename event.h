#ifndef EVENT_H
#define EVENT_H

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
    short repeatOfTask;
    short remindOfTask;
    QDate remindDate;
    QTime remindTime;
    QString descriptionOfTask;      //описание задачи
    QColor color;

public:
    Event(); //конструктор без комментария
    ~Event (){}
    void SetData (QString name, QDate sDate, QDate fDate,
                  QTime sTime, QTime fTime, short repeatCode, short remindCode, QString descript);
    void SetColor (QColor clr);
    QString GetNameOfTask();
    QDate GetStartDate();
    QDate GetFinishDate();
    QTime GetStartTime();
    QTime GetFinishTime();
    short GetRepeatOfTask ();
    short GetRemindOfTask ();
    QDate GetRemindDate ();
    QTime GetRemindTime ();
    QString GetDescriptionOfTask();
    QColor GetColor();

    void SetColor (QString);
    void SetNameOfTask(QString);
    void SetStartDate(QString);
    void SetFinishDate(QString);
    void SetStartTime(QString);
    void SetFinishTime(QString);
    void SetRepeatOfTask (short repeatCode);
    void SetRemindOfTask (short remindCode);
    void SetRemind ();
    void SetDescriptionOfTask(QString);
};
//

#endif // EVENT_H
