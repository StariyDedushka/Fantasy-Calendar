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

void CalendarView::slot_windowResized(quint16 wWidth, quint16 wHeight)
{
    m_calendarWidth = wWidth;
    m_calendarHeight = wHeight;
    emit signal_windowResized(wWidth, wHeight);
}
