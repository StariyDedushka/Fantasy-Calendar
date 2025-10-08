#ifndef EVENTVIEW_H
#define EVENTVIEW_H

#include <QObject>
#include <QGraphicsView>
#include "eventpainter.h"

class EventView : public QGraphicsView
{
    Q_OBJECT

signals:
    void signal_windowResized(quint16 wWidth, quint16 wHeight);

protected:
    void resizeEvent(QResizeEvent *event);
    quint16 m_windowWidth;
    quint16 m_windowHeight;
    EventPainter *painter;

public:
    EventView();
};

#endif // EVENTVIEW_H
