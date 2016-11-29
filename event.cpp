#include "event.h"
QString GetNameOfTask();
QDate GetStartDate();
QDate GetFinishDate();
QTime GetStartTime();
QTime GetFinishTime();
QString GetDescriptionOfTask();


Event::Event()
{
    nameOfTask = "";
    startDate = QDate::currentDate();
    finishDate = QDate::currentDate();
    startTime = QTime::currentTime();
    finishTime = QTime::currentTime();
    descriptionOfTask = "";
}



//Функция заполнения данных
void Event::SetData(QString name, QDate sDate, QDate fDate,
                    QTime sTime, QTime fTime, QString descript)
{
    nameOfTask = name;
    startDate = sDate;
    finishDate = fDate;
    startTime = sTime;
    finishTime = fTime;
    descriptionOfTask = descript;
}
//



//Установка цвета
void Event::SetColor (QColor clr)
{
    color = clr;
}
//

void Event::SetColor (QString scolor)
{
    color = scolor;
}



//Возврат названия задачи
QString Event::GetNameOfTask()
{
    return nameOfTask;
}
//



//Возврат нначальной даты задачи
QDate Event::GetStartDate()
{
    return startDate;
}
//



//Возврат конечной даты задачи
QDate Event::GetFinishDate()
{
    return finishDate;
}
//



//Возврат начального времени задачи
QTime Event::GetStartTime()
{
    return startTime;
}
//



//Возврат конечного времени задачи
QTime Event::GetFinishTime()
{
    return finishTime;
}
//



//Возврат описания задачи
QString Event::GetDescriptionOfTask()
{
    return descriptionOfTask;
}
//



//Возврат цвета
QColor Event::GetColor()
{
    return color;
}
//

void Event::SetNameOfTask(QString name)
{
    nameOfTask = name;
}

void Event::SetStartDate(QString date)
{
    startDate = QDate::fromString(date);
}

void Event::SetFinishDate(QString date)
{
    finishDate = QDate::fromString(date);
}

void Event::SetStartTime(QString time)
{
    startTime = QTime::fromString(time);
}

void Event::SetFinishTime(QString time)
{
    finishTime = QTime::fromString(time);
}

void Event::SetDescriptionOfTask(QString dscr)
{
    descriptionOfTask = dscr;
}
