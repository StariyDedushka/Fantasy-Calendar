#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

#include "CalendarScene.h"
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QDebug>
#include <QEvent>
#include <QTimer>

class CalendarView : public QGraphicsView
{
    Q_OBJECT
public:
    CalendarView();

// public slots:
//     void slot_windowResized(quint16 wWidth, quint16 wHeight);

private slots:
    void slot_redraw();

signals:
    void signal_windowResized(quint16 wWidth, quint16 wHeight);

protected:
    void mousePressEvent(QMouseEvent *event);
    CalendarScene *scene;
    quint16 m_calendarWidth;
    quint16 m_calendarHeight;
    void resizeEvent(QResizeEvent *event);
    QTimer *timer;
};

#endif // CALENDARVIEW_H
