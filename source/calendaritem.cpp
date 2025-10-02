#include "include/calendaritem.h"

CalendarItem::CalendarItem(const QRectF &rect, QDate date,  bool enabled, QGraphicsItem *parent ) :
    QGraphicsItem(parent)
    , m_date(date)
    , m_enabled(enabled)
    , m_rect(rect)
{
    CalendarItem::setAcceptHoverEvents(true);
}

CalendarItem::CalendarItem()
{

}

void CalendarItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Item clicked!";
}

QRectF CalendarItem::boundingRect() const
{
    qreal penWidth = 1;
    return QRectF(-10 - penWidth / 2, -10 - penWidth / 2,
                  20 + penWidth, 20 + penWidth);
}

void CalendarItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QBrush brush(Qt::lightGray);
    QPen pen(Qt::black);
    painter->setBrush(brush);
    painter->setPen(pen);
    painter->drawRect(m_rect);
    painter->drawText(m_rect, "День");
}
