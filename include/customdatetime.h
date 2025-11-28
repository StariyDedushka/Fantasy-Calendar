#ifndef CUSTOMDATETIME_H
#define CUSTOMDATETIME_H

#include <QObject>
#include "global_logger.h"
// #include "common/calendarstructures.h"

class CalendarSystem;

class CustomDateTime
{
private:
    quint32 m_day;
    quint32 m_dayAbsolute;
    quint32 m_month;
    quint32 m_year;
    quint32 m_hour;
    quint32 m_minute;
    quint32 m_second;

public:
    CustomDateTime();
    CustomDateTime(quint32 day, quint32 month, quint32 year,
                   quint32 hour = 0, quint32 minute = 0, quint32 second = 0);

    // Геттеры
    quint32 day() const { return m_day; }
    quint32 dayAbsolute() const { return m_dayAbsolute; }
    quint32 month() const { return m_month; }
    quint32 year() const { return m_year; }
    quint32 hour() const { return m_hour; }
    quint32 minute() const { return m_minute; }
    quint32 second() const { return m_second; }

    // Сеттеры с валидацией
    void setDate(quint32 day, quint32 month, quint32 year);
    void setDay(quint32 day);
    void setMonth(quint32 month);
    void setYear(quint32 year);
    void setTime(quint32 hour, quint32 minute, quint32 second = 0);
    void setDateTime(quint32 day, quint32 month, quint32 year,
                     quint32 hour, quint32 minute, quint32 second = 0);

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

