#include "include/calendaritem.h"

CalendarItem::CalendarItem(const QRectF &rect, quint16 day, quint16 month, quint32 year,  bool enabled, QGraphicsItem *parent ) :
    QGraphicsItem(parent)
    , m_day(day)
    , m_month(month)
    , m_year(year)
    , m_enabled(enabled)
    , m_rect(rect)
{
    m_hovered = false;
    CalendarItem::setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemIsFocusable, true);
}

CalendarItem::CalendarItem()
{
}

void CalendarItem::setRect(quint16 posX, quint16 posY, quint16 sizeX, quint16 sizeY)
{
    QPoint point(posX, posY);
    m_rect.setWidth(sizeX);
    m_rect.setHeight(sizeY);
    m_rect.setTopLeft(point);
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


void CalendarItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Item clicked!";
    emit signal_itemClicked(this);
    event->accept();
}

void CalendarItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    m_hovered = true;
    update();
    event->accept();
}

void CalendarItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    m_hovered = false;
    update();
    event->accept();
}


QRectF CalendarItem::boundingRect() const
{
    return m_rect;
}

void CalendarItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::lightGray);
    QBrush brushHover(Qt::darkGray);
    QPen pen(Qt::black);
    QPen hoverPen(Qt::white);
    if(m_hovered) {
        painter->setBrush(brushHover);
        painter->setPen(hoverPen);
        painter->drawRect(m_rect);
    } else {
        painter->setBrush(brush);
        painter->setPen(pen);
        painter->drawRect(m_rect);
    }
    painter->drawText(m_rect, "День " + QString::number(m_day));
}
