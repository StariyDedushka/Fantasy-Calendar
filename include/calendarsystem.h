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
    static quint16 h, m, s, ms;
    static quint16 m_day, m_month, m_year;
    QVector<Month*> *m_months;
    QVector<Day*> *m_days;

    quint16 m_secondsPerMinute = 60;
    quint16 m_minutesPerHour = 60;
    quint16 m_hoursPerDay = 24;

    quint16 m_daysInWeek = 7;
    quint16 m_monthsInYear = 12;

    static CalendarSystem* instance_ptr;
    CalendarSystem() { }

public:
    CalendarSystem(const CalendarSystem&) = delete;
    ~CalendarSystem() { instance_ptr = nullptr; }
    static CalendarSystem* getInstance();

    bool setHMS(quint16 h, quint16 m, quint16 s, quint16 ms = 0);
    bool setDMY(quint16 day, quint16 month, quint16 year);

    // Настройки времени
    quint16 secondsPerMinute() const { return m_secondsPerMinute; }
    quint16 minutesPerHour() const { return m_minutesPerHour; }
    quint16 hoursPerDay() const { return m_hoursPerDay; }

    // Настройки календаря
    quint16 daysInWeek() const { return m_daysInWeek; }
    quint16 monthsInYear() const { return m_monthsInYear; }

    void setTimeSystem(quint16 secPerMin, quint16 minPerHour, quint16 hoursPerDay);

    // Валидация даты
    bool isValidDate(quint16 day, quint16 month, quint32 year) const;

    // Утилиты
    Day* dayOfWeek(quint16 day = m_day, quint16 month = m_month, quint32 year = m_year) const;
    quint16 daysInMonth(quint16 month = m_month, quint32 year = m_year) const;
    quint32 daysInYear(quint16 year = 0) const;

    bool addMonth(const QString &name, quint16 days);
    bool addDayOfWeek(const QString &name, quint16 place = 0);
};

#endif // TimeSystem_H
