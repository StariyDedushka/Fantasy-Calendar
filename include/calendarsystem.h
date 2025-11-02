#ifndef TimeSystem_H
#define TimeSystem_H

#include <QObject>
#include "common/calendarStructures.h"

class CalendarSystem
{
    // Q_OBJECT

signals:
    void systemChanged();

private:
    quint16 h, m, s, ms;
    QVector<Month*> *m_months;
    QVector<Day*> *m_days;

    quint16 m_secondsPerMinute = 60;
    quint16 m_minutesPerHour = 60;
    quint16 m_hoursPerDay = 24;

    quint16 m_daysInWeek = 7;
    quint16 m_monthsInYear = 12;

public:
    CalendarSystem();
    CalendarSystem(const CalendarSystem&) = delete;
    ~CalendarSystem() {}

    // Настройки времени
    quint16 secondsPerMinute() const { return m_secondsPerMinute; }
    quint16 minutesPerHour() const { return m_minutesPerHour; }
    quint16 hoursPerDay() const { return m_hoursPerDay; }

    // Настройки календаря
    quint16 daysInWeek() const { return m_daysInWeek; }
    quint16 monthsInYear() const { return m_monthsInYear; }

    bool setTimeSystem(quint16 secPerMin, quint16 minPerHour, quint16 hoursPerDay);

    // Валидация даты
    bool isValidDate(quint16 day, quint16 month, quint32 year) const;

    // Утилиты
    Day* dayOfWeek(quint16 day) const;
    quint16 daysInMonth(quint16 month, quint32 year = 0) const;
    quint32 daysInYear(quint16 year = 0) const;

    bool addMonth(const QString &name, quint16 days, quint16 place = 0);
    bool removeMonth(const QString &name);
    bool removeMonth(quint16 id);

    bool editMonth(const QString& monthName, quint16 newDays = 0, const QString& newName = "");
    bool editMonth(quint16 month_id, quint16 newDays = 0, const QString& newName = "");
    bool moveMonth(const QString& monthName, quint16 newPlace);
    bool moveMonth(quint16 month_id, quint16 newPlace);

    bool addDayOfWeek(const QString &name, quint16 place = 0);
    bool removeDayOfWeek(const QString &name);
    bool removeDayOfWeek(quint16 id);

    bool editDayOfWeek(const QString& dayName, const QString& newName);
    bool editDayOfWeek(quint16 day_id, const QString& newName);
    bool moveDayOfWeek(quint16 day_id, quint16 newPlace);
    bool moveDayOfWeek(const QString& dayName, quint16 newPlace);

};

#endif // TimeSystem_H
