#include "include/eventcontainer.h"

EventContainer::EventContainer(const QRectF &rect,  QColor colorPrimary, QColor colorSecondary, QColor colorTertiary, bool enabled, QGraphicsItem *parent ) :
    AbstractItem(rect, colorPrimary, colorSecondary, colorTertiary, enabled, parent)
{
    m_expandable = true;
    CalendarEvent *testEvent = new CalendarEvent(QRectF(20, 40, 50, 30), Qt::darkGreen, Qt::darkGreen, Qt::yellow, true, this);
    addItem(testEvent);
    CalendarEvent *testEvent2 = new CalendarEvent(QRectF(50, 80, 100, 60), Qt::darkGreen, Qt::darkGreen, Qt::yellow, true, this);
    addItem(testEvent2);
    CalendarEvent *testEvent3 = new CalendarEvent(QRectF(20, 40, 50, 30), Qt::darkGreen, Qt::darkGreen, Qt::yellow, true, this);
    addItem(testEvent3);

}

// void EventContainer::mousePressEvent(QGraphicsSceneMouseEvent *event)
// {

//     if(m_selected) collapse();
//     else expand();


//     if (!m_enabled) {
//         qDebug() << "Item disabled, ignoring";
//         event->ignore();
//         return;
//     }
//     if (items)
//     {
//         if(!items.empty()) {
//             QPointF scenePos = event->scenePos();

//             for (AbstractItem *child : *items) {
//                 if (child->isEnabled() && child->isVisible()) {
//                     // Преобразуем позицию в координаты дочернего элемента
//                     QPointF childPos = child->mapFromScene(scenePos);
//                     if (child->contains(childPos)) {
//                         qDebug() << "Event should go to child:" << static_cast<void*>(child);
//                         event->ignore(); // Позволяем событию пройти к дочернему элементу
//                         return;
//                     }
//                 }
//             }
//         }
//     }
//     // Если дочерних элементов нет или событие не над ними - обрабатываем сами
//     qDebug() << "Handling event in parent";
//     toggleClicked();
//     emit signal_itemClicked(this);
//     event->accept();
//     update();

// }

void EventContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QBrush brush(colorPrimary);
    QBrush brushHover(colorDarken(colorPrimary));
    QBrush brushTriangle(colorTertiary);


    QPen pen(colorSecondary);
    QPen hoverPen(colorTertiary);

    if(m_hovered || m_selected) {
        painter->setBrush(brushHover);
        painter->setPen(hoverPen);
        painter->drawRect(m_rect);
    } else {
        painter->setBrush(brush);
        painter->setPen(pen);
        painter->drawRect(m_rect);
    }
    QSharedPointer<QPolygon> triangle = buildTriangle(m_rect, 100, static_cast<qint16>(m_selected * 90));
    painter->setBrush(brushTriangle);
    painter->drawPolygon(*triangle);
}
