#include "event.h"
Event::Event(QString name_of_event, date ds, date de)
{
    name = name_of_event;
    date_of_start.day = ds.day;
    date_of_start.month = ds.month;
    date_of_start.year = ds.year;
    date_of_end.day = de.day;
    date_of_end.month = de.month;
    date_of_end.year = de.year;
}
Event::Event(QString name_of_event, date ds, date de, QString com)
{
    name = name_of_event;
    date_of_start.day = ds.day;
    date_of_start.month = ds.month;
    date_of_start.year = ds.year;
    date_of_end.day = de.day;
    date_of_end.month = de.month;
    date_of_end.year = de.year;
    comment = com;
}
