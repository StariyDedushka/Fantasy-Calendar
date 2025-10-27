#ifndef CUSTOMDATETIME_H
#define CUSTOMDATETIME_H

#include <QObject>
#include "calendarsystem.h"
class CalendarSystem;

class CustomDateTime
{
private:
    quint16 m_day;
    quint16 m_month;
    quint32 m_year;
    quint16 m_hour;
    quint16 m_minute;
    quint16 m_second;

public:
    CalendarSystem *m_calendarSystem;
    CustomDateTime() : m_calendarSystem(nullptr) {}
    CustomDateTime(CalendarSystem* system);
    CustomDateTime(CalendarSystem* system, quint16 day, quint16 month, quint32 year,
                   quint16 hour = 0, quint16 minute = 0, quint16 second = 0);

    // Геттеры
    quint16 day() const { return m_day; }
    quint16 month() const { return m_month; }
    quint32 year() const { return m_year; }
    quint16 hour() const { return m_hour; }
    quint16 minute() const { return m_minute; }
    quint16 second() const { return m_second; }

    // Сеттеры с валидацией
    bool setDate(quint16 day, quint16 month, quint32 year);
    bool setTime(quint16 hour, quint16 minute, quint16 second = 0);
    bool setDateTime(quint16 day, quint16 month, quint32 year,
                     quint16 hour, quint16 minute, quint16 second = 0);

    // Валидация
    bool isValid() const;
    bool isValidDate() const;
    bool isValidTime() const;

    // Утилиты
    QString toString() const;
    Day* dayOfWeek() const;

    // Операции с датой/временем
    CustomDateTime addDays(qint32 days) const;
    CustomDateTime addHours(qint32 hours) const;

    // Сравнение
    bool operator==(const CustomDateTime& other) const;
    bool operator<(const CustomDateTime& other) const;
};

#endif // CUSTOMDATETIME_H

