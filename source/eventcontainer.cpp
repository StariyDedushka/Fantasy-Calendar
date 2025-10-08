#include "include/eventcontainer.h"

EventContainer::EventContainer(const QRectF &rect,  QColor fillColor, bool enabled, QGraphicsItem *parent ) :
    AbstractItem(rect, fillColor, enabled, parent)
{
    items = new QVector<AbstractItem*>();
    CalendarEvent *testEvent = new CalendarEvent(QRectF(0, 0, 50, 30), Qt::green);
    items->append(testEvent);

}

void EventContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
    while(!items->empty()) {
        int i = 0;
        items->at(i)->paint(painter, option, widget);

        i++;
    }
    update();
}
