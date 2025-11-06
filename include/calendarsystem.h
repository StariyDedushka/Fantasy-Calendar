#ifndef TimeSystem_H
#define TimeSystem_H

#include <QObject>
#include "include/common/calendarstructures.h"

class CalendarSystem
{
    // Q_OBJECT

signals:
    void systemChanged();

private:
    QVector<Month*> *m_months;
    QVector<Day*> *m_days;

    quint16 m_secondsPerMinute = 60;
    quint16 m_minutesPerHour = 60;
    quint16 m_hoursPerDay = 24;

    quint16 m_daysInWeek = 0;
    quint16 m_monthsInYear = 0;

public:
    CalendarSystem();
    CalendarSystem(const CalendarSystem&) = delete;
    ~CalendarSystem();

    // Настройки времени
    quint16 secondsPerMinute() const { return m_secondsPerMinute; }
    quint16 minutesPerHour() const { return m_minutesPerHour; }
    quint16 hoursPerDay() const { return m_hoursPerDay; }

    // Настройки календаря
    quint16 daysInWeek() const { return m_days->size(); }
    quint16 monthsInYear() const { return m_months->size(); }

    QVector<Month*>* months() const { return m_months; }
    QVector<Day*>* days() const { return m_days; }

    bool setTimeSystem(quint16 secPerMin, quint16 minPerHour, quint16 hoursPerDay);

    // Валидация даты
    bool isValidDate(quint16 day, quint16 month, quint32 year) const;

    // Утилиты
    Day* dayOfWeek(quint16 day) const;
    Day* firstDayOfMonth(quint16 month, quint32 year) const;
    quint16 daysInMonth(quint16 month, quint32 year = 0) const;
    quint32 daysInYear(quint32 year = 0) const;
    quint16 weeksInMonth(quint16 month, quint32 year = 0) const;

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
