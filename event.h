#ifndef EVENT_H
#define EVENT_H
#include <QString>
struct date
{
    short day, month, year;
};
class Event //класс события
{
    date date_of_start, date_of_end;
    QString name, comment;
public:
    Event(QString, date, date); //конструктор без комментария
    Event(QString, date, date, QString); //конструктор с комментарием
};
//
#endif // EVENT_H
