#include "include/calendarview.h"

CalendarView::CalendarView() {
    setDragMode(QGraphicsView::NoDrag);
}

void CalendarView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Custom view clicked.";
    QGraphicsView::mousePressEvent(event);
}
