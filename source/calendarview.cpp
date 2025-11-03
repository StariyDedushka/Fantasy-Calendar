#include "include/calendarview.h"

CalendarView::CalendarView() :
    scene(new CalendarScene())
{
    setDragMode(QGraphicsView::NoDrag);
    if (scene)
        connect(this, &CalendarView::signal_windowResized, scene, &CalendarScene::/*slot_*/windowResized);

    scene->initialize();
    setScene(scene);
    timer = new QTimer();
    timer->setSingleShot(true);
    timer->setInterval(25);
    connect(timer, &QTimer::timeout, this, &CalendarView::/*slot_*/redraw);
}

void CalendarView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void CalendarView::/*slot_*/redraw()
{
    // qDebug() << "Timeout redraw";
    // qDebug() << "Width:" << m_calendarWidth << ", height:" << m_calendarHeight;
    emit signal_windowResized(m_calendarWidth, m_calendarHeight);
}

void CalendarView::resizeEvent(QResizeEvent *event)
{
    timer->start();

    m_calendarWidth = this->width();
    m_calendarHeight = this->height();
    emit signal_windowResized(m_calendarWidth, m_calendarHeight);
}
