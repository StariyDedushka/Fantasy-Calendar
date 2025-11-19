#include "include/eventcontainer.h"
#include "include/customdatetime.h"

EventContainer::EventContainer(const QRectF &rect,
                               QString text,
                               QColor colorPrimary,
                               QColor colorSecondary,
                               QColor colorTertiary,
                               bool enabled,
                               QObject *parent) :
    AbstractItem(rect,
                text,
                colorPrimary,
                colorSecondary,
                colorTertiary,
                enabled,
                parent),
    m_expandable(true)
{
}


void EventContainer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    setupPainter(painter);
    QSharedPointer<QPolygon> triangle = buildTriangle(m_rect, 1.0, static_cast<qint16>(m_selected * 90));
    painter->drawPolygon(*triangle);
}

void EventContainer::addItem(AbstractItem *item)
{
    AbstractItem::addItem(item);
}
