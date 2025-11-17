#ifndef EVENTVISUALSTYLE_H
#define EVENTVISUALSTYLE_H

#include <QColor>
#include <QFont>
#include <QString>

struct EventVisualStyle {
    // Цвета
    QColor normalEventColor;
    QColor currentEventColor;
    QColor disabledEventColor;

    QColor normalTextColor;
    QColor currentTextColor;
    QColor disabledTextColor;

    QColor borderColor;
    QColor selectedBorderColor;
    QColor headerBackgroundColor;
    QColor headerTextColor;

    // Шрифты
    QFont eventFont;
    QFont headerFont;

    // Размеры и отступы
    int cellPadding;
    int borderWidth;
    int cornerRadius;

    // Конструктор с настройками по умолчанию
    EventVisualStyle() :
        normalEventColor(Qt::white),
        currentEventColor(QColor(200, 230, 255)),    // светло-голубой
        disabledEventColor(Qt::lightGray),

        normalTextColor(Qt::black),
        currentTextColor(Qt::darkBlue),
        disabledTextColor(Qt::darkGray),

        borderColor(Qt::gray),
        selectedBorderColor(Qt::blue),
        headerBackgroundColor(Qt::darkGray),
        headerTextColor(Qt::white),

        cellPadding(2),
        borderWidth(1),
        cornerRadius(4)
    {
        eventFont.setPointSize(10);
        headerFont.setPointSize(12);
        headerFont.setBold(true);
    }

    // Методы для получения цветов в зависимости от состояния
    QColor getBackgroundColor(bool isEnabled, bool isCurrent, bool isToday, bool isWeekend, bool hasEvents) const {
        if (!isEnabled) return disabledEventColor;
        if (isCurrent) return currentEventColor;
        return normalEventColor;
    }

    QColor getTextColor(bool isEnabled, bool isCurrent, bool isToday, bool isWeekend) const {
        if (!isEnabled) return disabledTextColor;
        if (isCurrent) return currentTextColor;
        return normalTextColor;
    }
};

#endif // EVENTVISUALSTYLE_H
