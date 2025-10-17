#include "include/calendaritem.h"

CalendarItem::CalendarItem(const QRectF &rect, QColor colorPrimary, QColor colorSecondary, QColor colorTertiary,
                 bool enabled, quint16 day, quint16 month, quint32 year) :

    AbstractItem(rect, colorPrimary, colorSecondary, colorTertiary, enabled)
    , m_day(day)
    , m_month(month)
    , m_year(year)
{
    m_expandable = false;
}


void CalendarItem::setDay(quint16 day)
{
    m_day = day;
}

void CalendarItem::setMonth(quint16 month)
{
    m_month = month;
}

void CalendarItem::setYear(quint32 year)
{
    m_year = year;
}

quint16 CalendarItem::day() const
{
    return m_day;
}

quint16 CalendarItem::month() const
{
    return m_month;
}

quint32 CalendarItem::year() const
{
    return m_year;
}


void CalendarItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    setupPainter(painter);
    painter->drawText(m_rect, "День " + QString::number(m_day));
}

bool CalendarItem::operator==(const CalendarItem& other)
{
    if(other.m_day == this->m_day && other.m_month == this->m_month
       && other.m_year == this->m_year && this->items == other.items)
        return true;
    else return false;
}
