#include "include/eventview.h"

EventView::EventView() {

    setDragMode(QGraphicsView::NoDrag);
    painter = new EventScene();
    emit signal_windowResized(this->width(), this->height());

    if (painter)
    {
        connect(this, &EventView::signal_windowResized, painter, &EventScene::slot_windowResized);
        connect(this, &EventView::signal_rebuild, painter, &EventScene::slot_rebuild);
    }
    emit signal_windowResized(this->width(), this->height());

    painter->initialize();
    setScene(painter);
    emit signal_rebuild(nullptr);
}

void EventView::resizeEvent(QResizeEvent *event)
{
    m_windowWidth = this->width();
    m_windowHeight = this->height();
    emit signal_windowResized(m_windowWidth, m_windowHeight);
}
