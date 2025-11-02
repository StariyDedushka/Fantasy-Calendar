#include "include/calendarsystem.h"


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

CalendarSystem::~CalendarSystem()
{
    for(Month *month : *m_months) delete month;
    for(Day *day : *m_days) delete day;
    delete m_months;
    delete m_days;
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
    else return nullptr;
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
    Q_UNUSED(year);
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
    day->id = m_days->size() + 1;

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
    month->id = m_months->size() + 1;

    m_months->insert(place, month);
    m_monthsInYear++;
    return true;
}


bool CalendarSystem::removeMonth(const QString &name)
{
    for(Month *month : *m_months)
    {
        if(month->name == name)
        {
            delete month;
            return true;
        }
    }
    return false;
}

bool CalendarSystem::removeMonth(quint16 id)
{
    for(Month *month : *m_months)
    {
        if(month->id == id)
        {
            delete month;
            return true;
        }
    }
    return false;
}

bool CalendarSystem::editMonth(const QString& monthName, quint16 newDays, const QString& newName)
{
    for(Month *month : *m_months)
    {
        if(month->name == monthName)
        {
            if(newDays == 0 && newName.isEmpty())
                return false;
            if(newDays != 0)
                month->days = newDays;
            if(newName != 0)
                month->name = newName;
            return true;
        }
    }
    return false;
}
bool CalendarSystem::editMonth(quint16 month_id, quint16 newDays, const QString& newName)
{
    for(Month *month : *m_months)
    {
        if(month->id == month_id)
        {
            if(newDays == 0 && newName.isEmpty())
                return false;
            if(newDays != 0)
                month->days = newDays;
            if(newName != 0)
                month->name = newName;
            return true;
        }
    }
    return false;
}

bool CalendarSystem::moveMonth(const QString& monthName, quint16 newPlace)
{
    for(Month *month : *m_months)
    {
        if(month->name == monthName)
        {
            m_months->insert(newPlace, std::move(month));
        }
    }
    return false;
}

bool CalendarSystem::moveMonth(quint16 month_id, quint16 newPlace)
{
    for(Month *month : *m_months)
    {
        if(month->id == month_id)
        {
            m_months->insert(newPlace, std::move(month));
        }
    }
    return false;

}

bool CalendarSystem::removeDayOfWeek(const QString &name);
bool CalendarSystem::removeDayOfWeek(quint16 id);

bool CalendarSystem::editDayOfWeek(const QString& dayName, const QString& newName);
bool CalendarSystem::editDayOfWeek(quint16 day_id, const QString& newName);
bool CalendarSystem::moveDayOfWeek(quint16 day_id, quint16 newPlace);
bool CalendarSystem::moveDayOfWeek(const QString& dayName, quint16 newPlace);
