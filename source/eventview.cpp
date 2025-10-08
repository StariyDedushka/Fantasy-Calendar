#include "include/eventview.h"

EventView::EventView() {
    painter = new EventPainter();
}

void EventView::resizeEvent(QResizeEvent *event)
{
    m_windowWidth = this->width();
    m_windowHeight = this->height();
    emit signal_windowResized(m_windowWidth, m_windowHeight);
}
