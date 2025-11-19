#ifndef CALENDARSTRUCTURES_H
#define CALENDARSTRUCTURES_H
#include <QObject>
#include <QColor>
#include "include/calendaritem.h"
#include "include/eventitem.h"
#include <QSize>

struct Month {
    quint32 id;
    quint16 position;
    quint16 days;
    QString name;
};

struct Day {
    quint16 id;
    quint16 position;
    QString name;
};

struct CalendarDayData {
    quint16 day;
    quint16 month;
    quint32 year;
    QString displayText;
    bool isEnabled;
    bool isCurrentDay;
    bool isToday;
    bool hasEvents;
    QColor backgroundColor;
    QColor textColor;
    QColor borderColor;
};

struct CalendarVisualData {
    QVector<CalendarItem*> items;
    QString headerText;
    QString weekDaysHeader;
    QSizeF cellSize;
    quint16 columns;
    quint16 rows;
};

struct CalendarEventData {
    quint32 id;
    QString displayText;
    bool isEnabled;
    bool isToday;
    QColor backgroundColor;
    QColor textColor;
    QColor borderColor;
};

struct EventVisualData {
    QVector<EventItem*> items;
    QString headerText;
    QSizeF cellSize;
    quint16 rows;
};

struct EventGroup {
    quint16 id;
    QString name;
    QColor color;
    // enum position {
    //     First,
    //     Middle,
    //     Last
    // };
};

#endif
