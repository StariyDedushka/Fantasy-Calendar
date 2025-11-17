#ifndef CUSTOMDATETIME_H
#define CUSTOMDATETIME_H

#include <QObject>
// #include "common/calendarstructures.h"

class CalendarSystem;

class CustomDateTime
{
private:
    quint16 m_day;
    quint32 m_dayAbsolute;
    quint16 m_month;
    quint32 m_year;
    quint16 m_hour;
    quint16 m_minute;
    quint16 m_second;

public:
    CustomDateTime();
    CustomDateTime(quint16 day, quint16 month, quint32 year,
                   quint16 hour = 0, quint16 minute = 0, quint16 second = 0);

    // Геттеры
    quint16 day() const { return m_day; }
    quint32 dayAbsolute() const { return m_dayAbsolute; }
    quint16 month() const { return m_month; }
    quint32 year() const { return m_year; }
    quint16 hour() const { return m_hour; }
    quint16 minute() const { return m_minute; }
    quint16 second() const { return m_second; }

    // Сеттеры с валидацией
    void setDate(quint16 day, quint16 month, quint32 year);
    void setDay(quint16 day);
    void setMonth(quint16 month);
    void setYear(quint16 year);
    void setTime(quint16 hour, quint16 minute, quint16 second = 0);
    void setDateTime(quint16 day, quint16 month, quint32 year,
                     quint16 hour, quint16 minute, quint16 second = 0);

    // Валидация
    bool isValid() const;

    // Утилиты
    QString toString() const;

    // Операции с датой/временем
    void addDays(qint32 days);
    void addHours(qint32 hours);
    void addMonths(qint32 months);
   // Сравнение
    bool operator==(const CustomDateTime& other) const;
    bool operator<(const CustomDateTime& other) const;
    bool operator>(const CustomDateTime& other) const;
    CustomDateTime& operator=(const CustomDateTime& other);
};

#endif // CUSTOMDATETIME_H

