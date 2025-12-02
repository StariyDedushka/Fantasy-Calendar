#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

#include "calendarscene.h"
#include "calendaritem.h"
#include "abstractview.h"


class CalendarScene;
struct CalendarVisualData;

class CalendarView : public AbstractView
{
    Q_OBJECT

public:
    explicit CalendarView(QWidget *parent = nullptr);
    ~CalendarView();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CALENDARVIEW_H
