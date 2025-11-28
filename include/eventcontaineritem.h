#ifndef EVENTCONTAINERITEM_H
#define EVENTCONTAINERITEM_H

#include <QObject>
#include "eventitem.h"

class EventContainerItem : public AbstractItem
{
    Q_OBJECT

public:
    EventContainerItem(const QRectF &rect, QString text = "", QColor colorPrimary = Qt::green, QColor colorSecondary = Qt::darkGreen,
                   QColor colorTertiary = Qt::yellow, bool enabled = true, QObject *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    // virtual void addItem(AbstractItem *item) override;
    QSharedPointer<QPolygon> buildTriangle(const QRectF &parentRect, double scale, qint16 rotation);
};

#endif // EVENTCONTAINERITEM_H
