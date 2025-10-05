#include "include/calendarview.h"

CalendarView::CalendarView() {
    setDragMode(QGraphicsView::NoDrag);
    scene = new CalendarPainter();
    connect(this, &CalendarView::signal_windowResized, scene, &CalendarPainter::slot_windowResized);
    scene->initialize();
    setScene(scene);
}

void CalendarView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Custom view clicked.";
    QGraphicsView::mousePressEvent(event);
}


void CalendarView::resizeEvent(QResizeEvent *event)
{
    m_calendarWidth = this->width();
    m_calendarHeight = this->height();
    emit signal_windowResized(m_calendarWidth, m_calendarHeight);
}
