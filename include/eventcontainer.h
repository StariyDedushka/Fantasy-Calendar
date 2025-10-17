#ifndef EVENTCONTAINER_H
#define EVENTCONTAINER_H

#include <QObject>
#include "calendarevent.h"

class EventContainer : public AbstractItem
{
    Q_OBJECT

private:
    // virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;


public:
    EventContainer();
    EventContainer(const QRectF &rect, QString text = "", QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen,
                   QColor colorTertiary = Qt::yellow, bool enabled = true, QObject *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // EVENTCONTAINER_H
