#ifndef CALENDARSTRUCTURES_H
#define CALENDARSTRUCTURES_H
#include <QObject>
#include <QColor>

struct Month {
    quint32 id;
    quint16 days;
    QString name;
};

struct Day {
    quint16 id;
    QString name;
};

struct EventGroup {
    quint16 id;
    QString name;
    QColor color;
    enum position {
        First,
        Normal,
        Last
    };
};

#endif
