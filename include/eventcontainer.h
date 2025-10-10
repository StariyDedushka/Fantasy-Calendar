#ifndef EVENTCONTAINER_H
#define EVENTCONTAINER_H

#include <QObject>
#include "calendarevent.h"

class EventContainer : public AbstractItem
{
    Q_OBJECT

private:
    QVector<CalendarEvent*> *m_events;

public:
    EventContainer();
    EventContainer(const QRectF &rect, QColor fillColor, bool enabled = true, QGraphicsItem *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // EVENTCONTAINER_H
