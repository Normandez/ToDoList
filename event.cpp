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
                    QTime sTime, QTime fTime, short repeatCode, short remindCode, QString descript)
{
    nameOfTask = name;
    startDate = sDate;
    finishDate = fDate;
    startTime = sTime;
    finishTime = fTime;
    repeatOfTask = repeatCode;
    remindOfTask = remindCode;
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



//Возврат кода повторения задачи
short Event::GetRepeatOfTask ()
{
    return repeatOfTask;
}
//



//Возврат кода напоминания задачи
short Event::GetRemindOfTask ()
{
    return remindOfTask;
}
//



//Возврат даты напоминания
QDate Event::GetRemindDate ()
{
    return remindDate;
}
//



//Возврат времени напоминания
QTime Event::GetRemindTime ()
{
    return remindTime;
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
    startDate = QDate::fromString(date, "dd.MM.yyyy");
}

void Event::SetFinishDate(QString date)
{
    finishDate = QDate::fromString(date, "dd.MM.yyyy");
}

void Event::SetStartTime(QString time)
{
    startTime = QTime::fromString(time, "hh:mm");
}

void Event::SetFinishTime(QString time)
{
    finishTime = QTime::fromString(time, "hh:mm");
}

void Event::SetRepeatOfTask (short repeatCode)
{
    repeatOfTask = repeatCode;
}

void Event::SetRemindOfTask (short remindCode)
{
    remindOfTask = remindCode;
}

void Event::SetDescriptionOfTask(QString dscr)
{
    descriptionOfTask = dscr;
}

void Event::SetRemind ()
{
    QTime bufTime = startTime;
    QDate bufDate = startDate;
    int hours = bufTime.hour();
    int minutes = bufTime.minute();
    int day = bufDate.day();
    int month = bufDate.month();
    int year = bufDate.year();

    //Напоминание за 1 минуту
    if (remindOfTask == 1)
    {
        minutes--;
        if (minutes < 0) {hours--; minutes = 59;}
        if (hours < 0) {day--; hours = 23;}
        if (day < 1) {month--; if(month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 2);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 5 минут
    if (remindOfTask == 2)
    {
        minutes = minutes - 5;
        if (minutes < 0) {hours--; minutes = 60 + minutes;}
        if (hours < 0) {day--; hours = 23;}
        if (day < 1) {month--; if(month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 10 минут
    if (remindOfTask == 3)
    {
        minutes = minutes - 10;
        if (minutes < 0) {hours--; minutes = 60 + minutes;}
        if (hours < 0) {day--; hours = 23;}
        if (day < 1) {month--; if(month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 15 минут
    if (remindOfTask == 4)
    {
        minutes = minutes - 15;
        if (minutes < 0) {hours--; minutes = 60 + minutes;}
        if (hours < 0) {day--; hours = 23;}
        if (day < 1) {month--; if(month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 20 минут
    if (remindOfTask == 5)
    {
        minutes = minutes - 20;
        if (minutes < 0) {hours--; minutes = 60 + minutes;}
        if (hours < 0) {day--; hours = 23;}
        if (day < 1) {month--; if(month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 25 минут
    if (remindOfTask == 6)
    {
        minutes = minutes - 25;
        if (minutes < 0) {hours--; minutes = 60 + minutes;}
        if (hours < 0) {day--; hours = 23;}
        if (day < 1) {month--; if(month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 30 минут
    if (remindOfTask == 7)
    {
        minutes = minutes - 30;
        if (minutes < 0) {hours--; minutes = 60 + minutes;}
        if (hours < 0) {day--; hours = 23;}
        if (day < 1) {month--; if(month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 45 минут
    if (remindOfTask == 8)
    {
        minutes = minutes - 45;
        if (minutes < 0) {hours--; minutes = 60 + minutes;}
        if (hours < 0) {day--; hours = 23;}
        if (day < 1) {month--; if(month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 1 час
    if (remindOfTask == 9)
    {
        hours--;
        if (hours < 0) {day--; hours = 23;}
        if (day < 1) {month--; if (month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 2 часа
    if (remindOfTask == 10)
    {
        hours = hours - 2;
        if (hours < 0) {day--; hours = 24 + hours;}
        if (day < 1) {month--; if (month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 3 часа
    if (remindOfTask == 11)
    {
        hours = hours - 3;
        if (hours < 0) {day--; hours = 24 + hours;}
        if (day < 1) {month--; if (month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 12 часов
    if (remindOfTask == 12)
    {
        hours = hours - 12;
        if (hours < 0) {day--; hours = 24 + hours;}
        if (day < 1) {month--; if (month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufTime.setHMS(hours, minutes, 10);
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 1 день
    if (remindOfTask == 13)
    {
        day--;
        if (day < 1) {month--; if (month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 2 дня
    if (remindOfTask == 14)
    {
        day = day - 2;
        if (day < 1) {month--; if (month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufDate.setDate(year, month, day);
    }
    //

    //Напоминание за 1 неделю
    if (remindOfTask == 15)
    {
        day = day - 7;
        if (day < 1) {month--; if (month > 0) bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        if (month < 1) {year--; month = 12; bufDate.setDate(year, month, 1); day = bufDate.daysInMonth();}
        bufDate.setDate(year, month, day);
    }
    //

    remindTime = bufTime;
    remindDate = bufDate;
}
