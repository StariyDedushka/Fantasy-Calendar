#ifndef CALENDARSTRUCTURES_H
#define CALENDARSTRUCTURES_H
#include <QObject>

struct Month {
    quint32 id;
    quint16 days;
    QString name;
};

struct Day {
    quint16 id;
    QString name;
};

#endif
