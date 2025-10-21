#include "include/eventcontainer.h"

EventContainer::EventContainer(const QRectF &rect, QString text,  QColor colorPrimary, QColor colorSecondary, QColor colorTertiary, bool enabled, QObject *parent ) :
    AbstractItem(rect, text, colorPrimary, colorSecondary, colorTertiary, enabled, parent)
{
    m_expandable = true;
    // CalendarEvent *testEvent = new CalendarEvent(QRectF(20, 40, 50, 30), Qt::darkGreen, Qt::darkGreen, Qt::yellow, true, this);
    // addItem(testEvent);
    // CalendarEvent *testEvent2 = new CalendarEvent(QRectF(50, 80, 100, 60), Qt::darkGreen, Qt::darkGreen, Qt::yellow, true, this);
    // addItem(testEvent2);
    // CalendarEvent *testEvent3 = new CalendarEvent(QRectF(20, 40, 50, 30), Qt::darkGreen, Qt::darkGreen, Qt::yellow, true, this);
    // addItem(testEvent3);

}

// void EventContainer::mousePressEvent(QGraphicsSceneMouseEvent *event)
// {
// }

void EventContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    setupPainter(painter);
    QSharedPointer<QPolygon> triangle = buildTriangle(m_rect, 1.0, static_cast<qint16>(m_selected * 90));
    painter->drawPolygon(*triangle);
}

void EventContainer::addItem(AbstractItem *item)
{
    AbstractItem::addItem(item);
}
