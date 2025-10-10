#include "include/eventview.h"

EventView::EventView() {

    setDragMode(QGraphicsView::NoDrag);
    painter = new EventPainter();
    emit signal_windowResized(this->width(), this->height());

    if (painter)
    {
        connect(this, &EventView::signal_windowResized, painter, &EventPainter::slot_windowResized);
        connect(this, &EventView::signal_rebuild, painter, &EventPainter::slot_rebuild);
    }
    emit signal_windowResized(this->width(), this->height());

    painter->initialize();
    setScene(painter);
    CalendarEvent *event = new CalendarEvent(QRectF(20, 10, 120, 40), Qt::red, true);
    QVector<AbstractItem*> *testVector = new QVector<AbstractItem*>();
    testVector->append(event);
    emit signal_rebuild(testVector);
}

void EventView::resizeEvent(QResizeEvent *event)
{
    m_windowWidth = this->width();
    m_windowHeight = this->height();
    emit signal_windowResized(m_windowWidth, m_windowHeight);
}
