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
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // EVENTVIEW_H
