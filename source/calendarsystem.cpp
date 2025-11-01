#include "include/calendarsystem.h"

CalendarSystem* CalendarSystem::instance_ptr = nullptr;

CalendarSystem::CalendarSystem() :
    m_months(new QVector<Month*>())
    , m_days(new QVector<Day*>())
    , m_monthsInYear(0)
    , m_daysInWeek(0)
    , m_secondsPerMinute(0)
    , m_minutesPerHour(0)
    , m_hoursPerDay(0)
{
}
CalendarSystem* CalendarSystem::getInstance()
{
    if(instance_ptr == nullptr)
    {
        instance_ptr = new CalendarSystem();
        return instance_ptr;
    }
    else throw std::runtime_error("Singleton CalendarSystem instance already exists!");
}

bool CalendarSystem::setTimeSystem(quint16 secPerMin, quint16 minPerHour, quint16 hoursPerDay)
{
    if(secPerMin < UINT16_MAX && minPerHour < UINT16_MAX && hoursPerDay < UINT16_MAX
       && (secPerMin > 0 && minPerHour > 0 && hoursPerDay > 0))
    {
        m_secondsPerMinute = secPerMin;
        m_minutesPerHour = minPerHour;
        m_hoursPerDay = hoursPerDay;
        return true;
    }
    return false;
}


bool CalendarSystem::isValidDate(quint16 day, quint16 month, quint32 year) const
{
    return (day >= 1 && day <= daysInMonth(month, year)) &&
           (month >= 1 && month <= m_monthsInYear) &&
           (year >= 1);
}

Day* CalendarSystem::dayOfWeek(quint16 day) const
{
    if(day > 0)
        return m_days->at(day - 1);
    else return new Day();
}

quint16 CalendarSystem::daysInMonth(quint16 month, quint32 year) const
{
    Q_UNUSED(year)
    if(!m_months->empty())
    return m_months->at(month - 1)->days;
    else return 0;
}


quint32 CalendarSystem::daysInYear(quint16 year) const
{
    quint32 daysInYear = 0;
    for(Month *month : *m_months)
        daysInYear += month->days;

    return daysInYear;
}

bool CalendarSystem::addDayOfWeek(const QString &name, quint16 place)
{
    if(place > m_daysInWeek)
        place = m_daysInWeek - 1;
    Day *day = new Day();
    day->name = name;
    m_days->insert(place, day);
    m_daysInWeek++;
    return true;
}

bool CalendarSystem::addMonth(const QString &name, quint16 days, quint16 place)
{
    if(place > m_months->size())
        place = m_months->size();
    Month *month = new Month();
    month->name = name;
    month->days = days;
    m_months->insert(place, month);
    m_monthsInYear++;
    return true;
}
// bool CalendarSystem::setDaysPerWeek(quint16 daysPerWeek)
// {
//     if(daysPerWeek < UINT16_MAX && (daysPerWeek > 0))
//     {
//         m_daysInWeek = daysPerWeek;
//         return true;
//     }
//     return false;
// }

bool CalendarSystem::editMonth(quint16 month_id, const QString& monthName, quint16 newDays, const QString &newName)
{
    auto searchMonth = [](Month *month) -> bool
    {
        month->days = newDays;
        if(!newName.isEmpty())
            month->name = newName;
        return true;
    };
    if((newDays < UINT16_MAX) && newDays > 0)
    {
        for(Month* month : *m_months)
        {
            if(month_id != 0)
            {
                if(month->id == month_id)
                {
                    searchMonth(month);
                }
            } else if(!monthName.isEmpty())
            {
                if(month->name == monthName)
                {
                    searchMonth(month);
                }
            }
        }
    }
    return false;
}
