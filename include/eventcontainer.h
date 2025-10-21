#ifndef EVENTCONTAINER_H
#define EVENTCONTAINER_H

#include <QObject>
#include "calendarevent.h"

class EventContainer : public AbstractItem
{
    Q_OBJECT

public:
    EventContainer(const QRectF &rect, QString text = "", QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen,
                   QColor colorTertiary = Qt::yellow, bool enabled = true, QObject *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void addItem(AbstractItem *item) override;
};

#endif // EVENTCONTAINER_H
