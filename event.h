#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QDate>
#include <QColor>



class Event : public QObject     //Класс задачи
{
    Q_OBJECT

private:
    QString nameOfTask;     //Название задачи
    QDate startDate;        //Дата начала
    QDate finishDate;       //Дата окончания
    QTime startTime;        //Время начала
    QTime finishTime;       //Время окончания
    short repeatOfTask;     //Код повторения
    short remindOfTask;     //Код напоминания
    short remindComplete = 0;       //Статус напоминания (совершено/несовершено)
    QDate remindDate;       //Дата напоминания
    QTime remindTime;       //Время напоминания
    QString descriptionOfTask;      //Описание задачи
    QColor color;       //Цвет задачи

public:
    Event(); //Пустой конструктор
    ~Event (){}
    void SetData (QString name, QDate sDate, QDate fDate,
                  QTime sTime, QTime fTime, short repeatCode, short remindCode, QString descript);      //Установка всех данных задачи в переменные класса
    void SetColor (QColor clr);     //Установка цвета
    QString GetNameOfTask();
    QDate GetStartDate();
    QDate GetFinishDate();
    QTime GetStartTime();
    QTime GetFinishTime();
    short GetRepeatOfTask ();
    short GetRemindOfTask();
    short GetRemindComplete();
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
    void SetRemindComplete (short code);
    void SetRemind ();      //Установить напоминание
    void SetRemindDate (QString date);
    void SetRemindTime (QString time);
    void SetDescriptionOfTask(QString);

};

#endif // EVENT_H
