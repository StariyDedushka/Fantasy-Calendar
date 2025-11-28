// src/customdatetime.cpp
#include "include/customdatetime.h"

CustomDateTime::CustomDateTime()
    : m_day(1),
    m_month(1),
    m_year(2000),
    m_hour(0),
    m_minute(0),
    m_second(0)
{
    LOG(INFO, logger, "Constructor without parameters called");
}

CustomDateTime::CustomDateTime(quint32 day, quint32 month, quint32 year,
                               quint32 hour, quint32 minute, quint32 second)
    : m_day(day),
    m_month(month),
    m_year(year),
    m_hour(hour),
    m_minute(minute),
    m_second(second)
{
    if(day == 0 || month == 0)
    {
        LOG(WARN, logger, "Tried constructing with invalid day/month, defaulting to 1/1");
        day = 1;
        month = 1;
    }
    LOG(INFO, logger, "Constructor with parameters called");
}

void CustomDateTime::setDate(quint32 day, quint32 month, quint32 year)
{
    m_day = day;
    m_month = month;
    m_year = year;
}

void CustomDateTime::setDay(quint32 day)
{
    m_day = day;
}

void CustomDateTime::setMonth(quint32 month)
{
    m_month = month;
}

void CustomDateTime::setYear(quint32 year)
{
    m_year = year;
}

void CustomDateTime::addDays(qint32 days)
{
    m_day += days;
}


void CustomDateTime::addMonths(qint32 months)
{
    m_month += months;
}

void CustomDateTime::setTime(quint32 hour, quint32 minute, quint32 second)
{
    m_hour = hour;
    m_minute = minute;
    m_second = second;
}

void CustomDateTime::setDateTime(quint32 day, quint32 month, quint32 year, quint32 hour, quint32 minute, quint32 second)
{
    m_day = day;
    m_month = month;
    m_year = year;

    m_hour = hour;
    m_minute = minute;
    m_second = second;
}

bool CustomDateTime::isValid() const
{
    // пока нет доступной логики валидации из-за отсутствия указателя на систему
    return true;
}

QString CustomDateTime::toString() const
{
    return QString("%1/%2/%3 - %4:%5:%6")
                    .arg(m_day).arg(m_month).arg(m_year)
                    .arg(m_hour).arg(m_minute).arg(m_second);
}


bool CustomDateTime::operator==(const CustomDateTime& other) const
{
    if(this->m_second == other.m_second
    && this->m_minute == other.m_minute
    && this->m_hour == other.m_hour
    && this->m_day == other.m_day
    && this->m_month == other.m_month
    && this->m_year == other.m_year)
        return true;
    else return false;
}

bool CustomDateTime::operator<(const CustomDateTime& other) const
{
    if(m_year > other.m_year)       return false;
    if(m_month > other.m_month)     return false;
    if(m_day > other.m_day)         return false;
    if(m_hour > other.m_hour)       return false;
    if(m_minute > other.m_minute)   return false;
    if(m_second > other.m_second)   return false;
    return true;
}

bool CustomDateTime::operator>(const CustomDateTime& other) const
{
    if(m_year > other.m_year)       return true;
    if(m_month > other.m_month)     return true;
    if(m_day > other.m_day)         return true;
    if(m_hour > other.m_hour)       return true;
    if(m_minute > other.m_minute)   return true;
    if(m_second > other.m_second)   return true;
    return false;
}

CustomDateTime& CustomDateTime::operator=(const CustomDateTime& other)
{
    if(this == &other)
        return *this;
    m_day = other.m_day;
    m_month = other.m_month;
    m_year = other.m_year;
    m_second = other.m_second;
    m_minute = other.m_minute;
    m_hour = other.m_hour;

    return *this;
}
