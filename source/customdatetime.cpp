// src/customdatetime.cpp
#include "include/customdatetime.h"

CustomDateTime::CustomDateTime(CalendarSystem* system)
    : m_calendarSystem(system), m_day(1), m_month(1), m_year(2000),
    m_hour(0), m_minute(0), m_second(0) {}

CustomDateTime::CustomDateTime(CalendarSystem* system, quint16 day, quint16 month,
                               quint32 year, quint16 hour, quint16 minute, quint16 second)
    : m_calendarSystem(system), m_day(day), m_month(month), m_year(year),
    m_hour(hour), m_minute(minute), m_second(second) {}

bool CustomDateTime::setDate(quint16 day, quint16 month, quint32 year)
{
    if (!m_calendarSystem->isValidDate(day, month, year))
        return false;

    m_day = day;
    m_month = month;
    m_year = year;
    return true;
}

bool CustomDateTime::addDays(qint32 days)
{
    m_day += days;
    m_day %= m_calendarSystem->daysInWeek();
    if(m_day > 0)
        return true;
    else return false;
}


bool CustomDateTime::addMonths(qint32 months)
{
    m_month += months;
    m_month %= m_calendarSystem->monthsInYear();
    if(m_month > 0)
        return true;
    else return false;
}

bool CustomDateTime::setTime(quint16 hour, quint16 minute, quint16 second)
{
    if (hour >= m_calendarSystem->hoursPerDay() ||
        minute >= m_calendarSystem->minutesPerHour() ||
        second >= m_calendarSystem->secondsPerMinute())
        return false;

    m_hour = hour;
    m_minute = minute;
    m_second = second;
    return true;
}

bool CustomDateTime::setDateTime(quint16 day, quint16 month, quint32 year, quint16 hour, quint16 minute, quint16 second)
{
    if (!m_calendarSystem->isValidDate(day, month, year))
        return false;

    m_day = day;
    m_month = month;
    m_year = year;

    if (hour >= m_calendarSystem->hoursPerDay() ||
        minute >= m_calendarSystem->minutesPerHour() ||
        second >= m_calendarSystem->secondsPerMinute())
        return false;

    m_hour = hour;
    m_minute = minute;
    m_second = second;
    return true;
}

bool CustomDateTime::isValid() const
{
    return isValidDate() && isValidTime();
}

bool CustomDateTime::isValidDate() const
{
    return m_calendarSystem->isValidDate(m_day, m_month, m_year);
}

bool CustomDateTime::isValidTime() const
{
    return m_hour < m_calendarSystem->hoursPerDay() &&
           m_minute < m_calendarSystem->minutesPerHour() &&
           m_second < m_calendarSystem->secondsPerMinute();
}

QString CustomDateTime::toString() const
{
    return QString("Day %1, Month %2, Year %3 - %4:%5:%6")
        .arg(m_day).arg(m_month).arg(m_year)
        .arg(m_hour).arg(m_minute).arg(m_second);
}

Day* CustomDateTime::dayOfWeek() const
{
    return m_calendarSystem->dayOfWeek(m_day);
}

bool CustomDateTime::operator==(const CustomDateTime& other) const
{
    if(this->m_second == other.m_second && this->m_minute == other.m_minute && this->m_hour == other.m_hour
        && this->m_day == other.m_day && this->m_month == other.m_month && this->m_year == other.m_year
        && this->m_calendarSystem == other.m_calendarSystem)
        return true;
    else return false;
}

bool CustomDateTime::operator<(const CustomDateTime& other) const
{
    if(m_year < other.m_year) return true;
    if(m_month < other.m_month) return true;
    if(m_day < other.m_day) return true;
    if(m_hour < other.m_hour) return true;
    if(m_minute < other.m_minute) return true;
    if(m_second < other.m_second) return true;
    return false;
}
