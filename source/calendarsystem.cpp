#include "include/calendarsystem.h"


CalendarSystem::CalendarSystem() :
    m_months(new QVector<Month*>())
    , m_days(new QVector<Day*>())
    , m_daysInWeek(0)
    , m_monthsInYear(0)
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
    LOG(INFO, logger, "Object destroyed");
}

bool CalendarSystem::setTimeSystem(quint16 secPerMin, quint16 minPerHour, quint16 hoursPerDay)
{
    if(secPerMin < UINT16_MAX && minPerHour < UINT16_MAX && hoursPerDay < UINT16_MAX
       && (secPerMin > 0 && minPerHour > 0 && hoursPerDay > 0))
    {
        m_secondsPerMinute = secPerMin;
        m_minutesPerHour = minPerHour;
        m_hoursPerDay = hoursPerDay;
        LOG(INFO, logger, QString("Set time system to spm: %1, mph: %2, hpd: %3")
                                  .arg(secPerMin).arg(minPerHour).arg(hoursPerDay);
        return true;
    }
    LOG(WARN, logger, "Couldn't set time system");
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


quint32 CalendarSystem::daysInYear(quint32 year) const
{
    Q_UNUSED(year);
    quint32 daysInYear = 0;
    for(Month *month : *m_months)
        daysInYear += month->days;

    return daysInYear;
}

Day* CalendarSystem::firstDayOfMonth(quint16 month, quint32 year) const
{
    quint32 days = 0;
    days = daysInYear() * year;
    for(int i = 0; i < month; i++)
    {
        days += months()->at(i)->days;
    }
    return dayOfWeek(days % daysInWeek());

}

quint16 CalendarSystem::weeksInMonth(quint16 month, quint32 year) const
{
    Q_UNUSED(year)
    if(m_months)
        return m_months->at(month - 1)->days / daysInWeek();
    return 0;
}

bool CalendarSystem::addDayOfWeek(const QString &name, quint16 place)
{

    Day *day = new Day();
    day->name = name;
    day->id = m_days->size() + 1;
    day->position = day->id;

    if(name.isEmpty())
    {
        LOG(ERROR, logger, "Tried adding a day with an empty name");
        return false;
    }

    if(place > m_daysInWeek)
        m_days->append(day);
    else
        m_days->insert(place, day);
    m_daysInWeek++;
    LOG(INFO, logger, QString("Added day of week: %1, №%2").arg(name).arg(place));
    return true;
}

bool CalendarSystem::addMonth(const QString &name, quint16 days, quint16 place)
{
    if(place > m_months->size())
        place = m_months->size();
    if(name.isEmpty())
    {
        LOG(ERROR, logger, "Tried adding a month with an empty name");
        return false;
    }
    if(!(days > 0))
    {
        LOG(ERROR, logger, "Tried adding a month with zero days");
        return false;
    }

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
            try
                delete month;
            catch
                LOG(FATAL, logger, QString("Trying to free unallocated memory").arg(name));
            LOG(INFO, logger, QString("Deleted month %1 succesfully").arg(name));
            return true;
        }
    }
    LOG(ERROR, logger, QString("Couldn't delete month %1").arg(name));
    return false;
}

bool CalendarSystem::removeMonth(quint16 id)
{
    for(Month *month : *m_months)
    {
        if(month->id == id)
        {
            try
                delete month;
            catch
                LOG(FATAL, logger, QString("Trying to free unallocated memory").arg(id));
            LOG(INFO, logger, QString("Deleted month with id %1 succesfully").arg(id));
            return true;
        }
    }
    LOG(ERROR, logger, QString("Couldn't delete month with id %1").arg(name));
    return false;
}

bool CalendarSystem::editMonth(const QString name, quint16 newDays)
{
    if(newDays == 0)
    {
        LOG(ERROR, logger, QString("Tried to change month %1's total days to 0").arg(name));
        return false;
    }

    for(Month *month : *m_months)
    {
        if(month->name == name)
        {
            month->days = newDays;
            LOG(INFO, logger, QString("Changed month %1's total days to %2").arg(name).arg(newDays));
            return true;
        }
    }
    LOG(ERROR, logger, QString("Couldn't find month named %1").arg(name));
    return false;
}

bool CalendarSystem::editMonth(quint16 id, const QString& newName)
{
    for(Month *month : *m_months)
    {
        if(month->id == id)
        {
            try
                month->name = newName;
            catch {
                LOG(FATAL, logger, QString("Trying to change month %1's name to undefined").arg(id));
                return false;
            }
            LOG(INFO, logger, QString("Changed month with id %1's name to %2").arg(id).arg(newName));
            return true;
        }
    }
    return false;
}

bool CalendarSystem::editMonth(quint16 id, quint16 newDays)
{
    if(newDays == 0)
    {
        LOG(ERROR, logger, QString("Tried to change month with id %1's total days to 0").arg(id));
        return false;
    }

    for(Month *month : *m_months)
    {
        if(month->id == id)
        {
            month->days = newDays;
            LOG(INFO, logger, QString("Changed month with id %1's total days to %2").arg(id).arg(newDays));
            return true;
        }
    }
    LOG(ERROR, logger, QString("Couldn't find month with id %1").arg(id));
    return false;
}

bool CalendarSystem::moveMonth(const QString& name, quint16 newPlace)
{
    if(newPlace > m_months->size())
    {
        LOG(WARN, logger, QString("Month %1's new place is greater than total array size, defaulting to last place").arg(name));
        newPlace = m_months->size();
    }

    for(Month *month : *m_months)
    {
        if(month->name == name)
        {
            m_months->move(m_months->indexOf(month), newPlace));
            LOG(INFO, logger, QString("Moved month %1 to position %2").arg(name).arg(newPlace));
            return true;
        }
    }
    LOG(ERROR, logger, QString("Couldn't find month named %1").arg(name));
    return false;
}

bool CalendarSystem::moveMonth(quint16 id, quint16 newPlace)
{
    if(newPlace > m_months->size())
    {
        LOG(WARN, logger, QString("Month %1's new place is greater than total array size, defaulting to last place").arg(id));
        newPlace = m_months->size();
    }

    for(Month *month : *m_months)
    {
        if(month->id == id)
        {
            m_months->move(m_months->indexOf(month), newPlace);
            LOG(INFO, logger, QString("Moved month %1 to position %2").arg(id).arg(newPlace));
            return true;
        }
    }
    LOG(ERROR, logger, QString("Couldn't find month named %1").arg(name));
    return false;
}


bool CalendarSystem::removeDayOfWeek(const QString &name)
{
    int i = 0;
    for(Day *day : *m_days)
    {
        i++;
        if(day->id == id)
        {
            try
            {
                delete m_days->at(i);
                m_days->remove(i);
            } catch ()
            {
                LOG(FATAL, logger, "Trying to free unallocated memory");
                return false;
            }
            LOG(INFO, logger, QString("Deleted day %1 succesfully").arg(id));
            return true;
        }
    }
    LOG(ERROR, logger, QString("Couldn't delete month with id %1").arg(name));
    return false;

}

bool CalendarSystem::removeDayOfWeek(quint16 id)
{
    int i = 0;
    for(Day *day : *m_days)
    {
        i++;
        if(day->id == id)
        {
            try
            {
                delete m_days->at(i);
                m_days->remove(i);
            } catch ()
            {
                LOG(FATAL, logger, "Trying to free unallocated memory");
                return false;
            }
            LOG(INFO, logger, QString("Deleted day %1 succesfully").arg(id));
            return true;
        }
    }
    LOG(ERROR, logger, QString("Couldn't delete month with id %1").arg(name));
    return false;
}

bool CalendarSystem::editDayOfWeek(const QString& dayName, const QString& newName)
{
    for(Day *day : *m_days)
    {
        if(day->name == dayName)
        {
            day->name = newName;
            return true;
        }
    }
    return false;
}

bool CalendarSystem::editDayOfWeek(quint16 day_id, const QString& newName)
{
    for(Day *day : *m_days)
    {
        if(day->id == day_id)
        {
            day->name = newName;
            return true;
        }
    }
    return false;
}

bool CalendarSystem::moveDayOfWeek(quint16 day_id, quint16 newPlace)
{
    for(Day *day : *m_days)
    {
        if(day->id == day_id)
        {
            day->position = newPlace;
            return true;
        }
    }
    return false;
}

bool CalendarSystem::moveDayOfWeek(const QString& dayName, quint16 newPlace)
{
    for(Day *day : *m_days)
    {
        if(day->name == dayName)
        {
            day->position = newPlace;
            return true;
        }
    }
    return false;
}
