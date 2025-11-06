#ifndef CALENDARSTRUCTURES_H
#define CALENDARSTRUCTURES_H
#include <QObject>
#include <QColor>
#include <QSize>

struct Month {
    quint32 id;
    quint16 position;
    quint16 days;
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
    QVector<CalendarDayData> days;
    QString headerText;
    QString weekDaysHeader;
    QSize gridSize; // columns x rows
    QSizeF cellSize;
};

struct Day {
    quint16 id;
    quint16 position;
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
