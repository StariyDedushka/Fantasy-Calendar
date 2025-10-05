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

protected:
    void mousePressEvent(QMouseEvent *event);
    CalendarPainter *scene;
};

#endif // CALENDARVIEW_H
