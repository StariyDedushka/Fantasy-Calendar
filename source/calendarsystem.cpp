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


bool CalendarSystem::isValidDate(quint16 day, quint16 month, quint32 year) const
{
    return (day >= 1 && day <= daysInMonth(month, year)) &&
           (month >= 1 && month <= m_monthsInYear) &&
           (year >= 1);
}

Day* CalendarSystem::dayOfWeek(quint16 day, quint16 month, quint32 year) const
{
    quint32 totalDays = (year - 1) * daysInYear() +
                        (month - 1) * daysInMonth(month, year) +
                        (day - 1);
    return m_days->at(totalDays % m_daysInWeek + 1);
}

quint16 CalendarSystem::daysInMonth(quint16 month, quint32 year) const
{
    Q_UNUSED(year)
    return m_months->at(month - 1)->days;
}


quint32 CalendarSystem::daysInYear(quint16 year) const
{
    quint32 daysInYear = 0;
    for(int i = 0; i < m_months->size(); i++)
    {
        daysInYear += m_months->at(i)->days;
    }
    return daysInYear;
}
