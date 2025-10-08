#ifndef EVENTCONTAINER_H
#define EVENTCONTAINER_H

#include <QObject>
#include "calendarevent.h"

class EventContainer : public AbstractItem
{
    Q_OBJECT
public:
    EventContainer();
    EventContainer(const QRectF &rect, QColor fillColor, bool enabled = true, QGraphicsItem *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    // QVector<CalendarEvent*> *m_events;
};

#endif // EVENTCONTAINER_H
