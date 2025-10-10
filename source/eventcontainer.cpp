#include "include/eventcontainer.h"

EventContainer::EventContainer(const QRectF &rect,  QColor fillColor, bool enabled, QGraphicsItem *parent ) :
    AbstractItem(rect, fillColor, enabled, parent)
{
    items = new QVector<AbstractItem*>();
    QColor eventColor(150, 150, 150, 90);
    CalendarEvent *testEvent = new CalendarEvent(QRectF(20, 40, 50, 30), eventColor, true, this);
    addItem(testEvent);
    CalendarEvent *testEvent2 = new CalendarEvent(QRectF(20, 100, 50, 30), eventColor, true, this);
    addItem(testEvent2);
    CalendarEvent *testEvent3 = new CalendarEvent(QRectF(20, 160, 50, 30), eventColor, true, this);
    addItem(testEvent3);

}

void EventContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QColor hoverColor(colorDarken(m_fillColor));

    QBrush brush(m_fillColor);
    QBrush brushHover(hoverColor);

    QColor outlineColor(colorDarken(m_fillColor));
    QColor hoverOutlineColor(m_fillColor);

    QPen pen(outlineColor);
    QPen hoverPen(hoverOutlineColor);

    if(m_hovered || m_selected) {
        painter->setBrush(brushHover);
        painter->setPen(hoverPen);
        painter->drawRect(m_rect);
    } else {
        painter->setBrush(brush);
        painter->setPen(pen);
        painter->drawRect(m_rect);
    }
    QPolygon *triangle = drawTriangle(30, 50, 100, 0);
    painter->drawPolygon(*triangle);
}
