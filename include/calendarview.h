#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

#include <include/calendarpainter.h>
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QDebug>
#include <QEvent>

class CalendarView : public QGraphicsView
{
    Q_OBJECT
public:
    CalendarView();

// public slots:
//     void slot_windowResized(quint16 wWidth, quint16 wHeight);

signals:
    void signal_windowResized(quint16 wWidth, quint16 wHeight);

protected:
    void mousePressEvent(QMouseEvent *event);
    CalendarPainter *scene;
    quint16 m_calendarWidth;
    quint16 m_calendarHeight;
    void resizeEvent(QResizeEvent *event);
};

#endif // CALENDARVIEW_H
