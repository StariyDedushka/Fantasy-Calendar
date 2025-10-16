#include "include/calendarsystem.h"

CalendarSystem* CalendarSystem::instance_ptr = nullptr;

CalendarSystem* CalendarSystem::getInstance()
{
    if(instance_ptr == nullptr)
        instance_ptr = new CalendarSystem();
    return instance_ptr;
}

void CalendarSystem::setTimeSystem(quint16 secPerMin, quint16 minPerHour, quint16 hoursPerDay)
{
    m_secondsPerMinute = secPerMin;
    m_minutesPerHour = minPerHour;
    m_hoursPerDay = hoursPerDay;
}

void CalendarSystem::setCalendarSystem(quint16 daysPerWeek, quint16 daysPerMonth,
                                       quint16 monthsPerYear, quint16 daysPerYear)
{
    m_daysPerWeek = daysPerWeek;
    m_daysPerMonth = daysPerMonth;
    m_monthsPerYear = monthsPerYear;
    m_daysPerYear = daysPerYear;
}

bool CalendarSystem::isValidDate(quint16 day, quint16 month, quint32 year) const
{
    return (day >= 1 && day <= m_daysPerMonth) &&
           (month >= 1 && month <= m_monthsPerYear) &&
           (year >= 1);
}

quint16 CalendarSystem::dayOfWeek(quint16 day, quint16 month, quint32 year) const
{
    quint32 totalDays = (year - 1) * m_daysPerYear +
                        (month - 1) * m_daysPerMonth +
                        (day - 1);
    return (totalDays % m_daysPerWeek) + 1;
}

quint16 CalendarSystem::daysInMonth(quint16 month, quint32 year) const
{
    Q_UNUSED(year)
    return m_daysPerMonth;
}
