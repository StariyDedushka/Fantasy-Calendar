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

struct ItemData {
    QString displayText;
    bool isEnabled;
    QColor backgroundColor;
    QColor textColor;
    QColor borderColor;
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
};

struct SceneVisualData {
    QVector<ItemData*> items;
    QSizeF cellSize;
    quint16 columns;
    quint16 rows;
    QMap<QString, QString> headers;
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
