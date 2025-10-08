#include "include/calendaritem.h"

CalendarItem::CalendarItem(const QRectF &rect, QColor fillColor, bool enabled, quint16 day, quint16 month, quint32 year) :

    AbstractItem(rect, fillColor, enabled)
    , m_day(day)
    , m_month(month)
    , m_year(year)
{
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
    QBrush brush(Qt::lightGray);
    QBrush brushHover(Qt::darkGray);
    QPen pen(Qt::black);
    QPen hoverPen(Qt::white);
    if(m_hovered || m_selected) {
        painter->setBrush(brushHover);
        painter->setPen(hoverPen);
        painter->drawRect(m_rect);
    } else {
        painter->setBrush(brush);
        painter->setPen(pen);
        painter->drawRect(m_rect);
    }
    painter->drawText(m_rect, "День " + QString::number(m_day));
    update();
}
