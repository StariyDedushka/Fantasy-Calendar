#ifndef CALENDARSTRUCTURES_H
#define CALENDARSTRUCTURES_H
#include <QObject>
#include "include/calendaritem.h"

struct Month {
    quint32 id;
    QString *name;
    QVector<CalendarItem*> days;
};

#endif
