#ifndef STRUCTS_H
#define STRUCTS_H
#include <QObject>
#include <QColor>
#include "include/calendaritem.h"
#include "include/eventitem.h"
#include "include/eventcontaineritem.h"
#include <QSize>

struct DayOfWeek {
    QString name;
    quint32 id;
    quint32 position;
    bool hasEvents;
};

struct Month {
    QString name;
    // QVector<quint32> days;
    quint32 id;
    quint32 position;
    quint32 daysTotal;
};

struct Event {
    CustomDateTime time;
    QString name;
    QString text;
    quint32 id;
    quint32 dayId;
    quint32 groupId;
};

// struct DayData {
//     QString name;
//     quint32 id;
//     bool hasEvents;
//     // QList<quint32> events;
// };

struct ItemData {
    QMap<QString, QString> displayText;
    QColor backgroundColor;
    QColor textColor;
    QColor borderColor;
    bool isEnabled;
};

struct CalendarDayData : ItemData {
    quint32 day;
    quint32 month;
    quint32 year;
    bool isCurrentDay;
    bool isToday;
    bool hasEvents;
};

struct CalendarEventData : ItemData {
    quint32 id;
    quint32 hour;
    quint32 minute;
    quint32 second;
};

struct EventContainerData : ItemData {
    quint32 id;
};

struct SceneVisualData {
    QVector<ItemData*> items;
    QSizeF cellSize;
    quint16 columns;
    quint16 rows;
    QMap<QString, QString> headers;
};



#endif
