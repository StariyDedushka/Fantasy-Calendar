#ifndef EVENTVIEW_H
#define EVENTVIEW_H


#include "eventscene.h"

#include "abstractview.h"


class EventView : public AbstractView
{
    Q_OBJECT

public:
    explicit EventView(QWidget *parent = nullptr);
    ~EventView();

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // EVENTVIEW_H
