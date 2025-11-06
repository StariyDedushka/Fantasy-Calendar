#ifndef CALENDARVISUALSTYLE_H
#define CALENDARVISUALSTYLE_H

#include <QColor>
#include <QFont>
#include <QString>

struct CalendarVisualStyle {
    // Цвета
    QColor normalDayColor;
    QColor currentDayColor;
    QColor todayColor;
    QColor weekendColor;
    QColor disabledDayColor;
    QColor eventDayColor;

    QColor normalTextColor;
    QColor currentTextColor;
    QColor todayTextColor;
    QColor weekendTextColor;
    QColor disabledTextColor;

    QColor borderColor;
    QColor selectedBorderColor;
    QColor headerBackgroundColor;
    QColor headerTextColor;

    // Шрифты
    QFont dayFont;
    QFont headerFont;
    QFont weekDaysFont;

    // Размеры и отступы
    int cellPadding;
    int borderWidth;
    int cornerRadius;

    // Конструктор с настройками по умолчанию
    CalendarVisualStyle() :
        normalDayColor(Qt::white),
        currentDayColor(QColor(200, 230, 255)),    // светло-голубой
        todayColor(QColor(255, 255, 200)),         // светло-желтый
        weekendColor(QColor(255, 240, 240)),       // светло-красный
        disabledDayColor(Qt::lightGray),
        eventDayColor(QColor(255, 230, 200)),      // светло-оранжевый

        normalTextColor(Qt::black),
        currentTextColor(Qt::darkBlue),
        todayTextColor(Qt::red),
        weekendTextColor(Qt::darkRed),
        disabledTextColor(Qt::darkGray),

        borderColor(Qt::gray),
        selectedBorderColor(Qt::blue),
        headerBackgroundColor(Qt::darkGray),
        headerTextColor(Qt::white),

        cellPadding(2),
        borderWidth(1),
        cornerRadius(4)
    {
        dayFont.setPointSize(10);
        headerFont.setPointSize(12);
        headerFont.setBold(true);
        weekDaysFont.setPointSize(9);
    }

    // Методы для получения цветов в зависимости от состояния
    QColor getBackgroundColor(bool isEnabled, bool isCurrent, bool isToday, bool isWeekend, bool hasEvents) const {
        if (!isEnabled) return disabledDayColor;
        if (isToday) return todayColor;
        if (isCurrent) return currentDayColor;
        if (hasEvents) return eventDayColor;
        if (isWeekend) return weekendColor;
        return normalDayColor;
    }

    QColor getTextColor(bool isEnabled, bool isCurrent, bool isToday, bool isWeekend) const {
        if (!isEnabled) return disabledTextColor;
        if (isToday) return todayTextColor;
        if (isCurrent) return currentTextColor;
        if (isWeekend) return weekendTextColor;
        return normalTextColor;
    }
};

#endif // CALENDARVISUALSTYLE_H
