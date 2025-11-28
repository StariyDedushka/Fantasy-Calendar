#ifndef STRUCTS_H
#define STRUCTS_H
#include <QObject>
#include <QColor>
#include "include/calendaritem.h"
#include "include/eventitem.h"
#include "include/eventcontaineritem.h"
#include <QSize>

struct DayOfWeek {
    quint32 id;
    quint32 position;
    QString name;
};

struct Month {
    quint32 id;
    quint32 position;
    quint32 daysTotal;
    QString name;
    QVector<quint32> days;
};

struct Event {
    quint32 id;
    quint32 groupId;
    CustomDateTime time;
    QString name;
    QString text;
};

struct DayData {
    quint32 id;
    QString name;
    QList<quint32> events;
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
    QVector<CalendarDayData*> items;
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
    QColor backgroundColor;
    QColor textColor;
    QColor borderColor;
};

struct EventContainerData {
    quint32 id;
    QString headerText;
    bool isEnabled;
    QColor backgroundColor;
    QColor textColor;
    QColor borderColor;
};

struct EventVisualData {
    QVector<EventContainerItem*> items;
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
