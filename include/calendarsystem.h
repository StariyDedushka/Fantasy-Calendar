#ifndef TimeSystem_H
#define TimeSystem_H

#include <QObject>

class CalendarSystem
{
    // Q_OBJECT
private:
    quint16 h, m, s, ms;
    quint16 day, month, year;
    

signals:
    void systemChanged();

private:
    quint16 m_secondsPerMinute = 60;
    quint16 m_minutesPerHour = 60;
    quint16 m_hoursPerDay = 24;

    quint16 m_daysPerWeek = 7;
    quint16 m_daysPerMonth = 30;
    quint16 m_monthsPerYear = 12;
    quint16 m_daysPerYear = 365;

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
    quint16 daysPerWeek() const { return m_daysPerWeek; }
    quint16 daysPerMonth() const { return m_daysPerMonth; }
    quint16 monthsPerYear() const { return m_monthsPerYear; }
    quint16 daysPerYear() const { return m_daysPerYear; }

    void setTimeSystem(quint16 secPerMin, quint16 minPerHour, quint16 hoursPerDay);
    void setCalendarSystem(quint16 daysPerWeek, quint16 daysPerMonth,
                           quint16 monthsPerYear, quint16 daysPerYear);

    // Валидация даты
    bool isValidDate(quint16 day, quint16 month, quint32 year) const;

    // Утилиты
    quint16 dayOfWeek(quint16 day, quint16 month, quint32 year) const;
    quint16 daysInMonth(quint16 month, quint32 year) const;
};

#endif // TimeSystem_H
