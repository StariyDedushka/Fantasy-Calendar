#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

#include "calendarscene.h"
#include "calendaritem.h"
#include "abstractview.h"



class CalendarView : public AbstractView
{
    Q_OBJECT

public:
    explicit CalendarView(QWidget *parent = nullptr);
    ~CalendarView();

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CALENDARVIEW_H
